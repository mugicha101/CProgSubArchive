import json
from curl_cffi import requests
import time
from pathlib import Path
import random
import os
import re

API_URL = "https://solved.ac/api/v3/search/problem"
class API:
  def call(*args, **kwargs):
    now = time.time()
    wait_time = 1
    res = None
    while res is None:
      time.sleep(random.expovariate(1/wait_time)) # rate limit
      wait_time *= 2
      print(f"[{now}] API call: {args} {kwargs}")
      try:
        res = requests.get(*args, impersonate="chrome", **kwargs)
        if res is None or res.status_code != 200:
          print(f"Error: {res.status_code if res else 'Unknown'}, retrying...")
      except Exception as e:
        print(f"Exception during API call: {e}, retrying...")
        res = None
    return res
  
  def get_problem(problem_id):
    res = API.call(API_URL, params={
      "query": f"id:{problem_id}"
    })
    if res.status_code == 200:
      return res.json()
    else:
      print(f"Error: {res.status_code}")
      return None
    
def secure_filename(filename):
    # Split the name and the extension
    name, ext = os.path.splitext(filename)
    
    # Keep Unicode word characters (Korean, English, numbers), spaces, and hyphens
    # Strip everything else out
    safe_name = re.sub(r'[^\w\s-]', '', name)
    
    # Replace spaces with underscores for web-safety
    safe_name = safe_name.strip().replace(' ', '_')
    
    return f"{safe_name}{ext}"

def get_tier(level):
  if level <= 0:
    return "unrated"
  if level > 30:
    return f"Tier {level}"
  return ["bronze", "silver", "gold", "platinum", "diamond", "ruby"][(level-1)//5] + f"{(5 - (level-1)%5)}"

def main():
  files = list(Path("./raw").iterdir())
  nfiles = len(files)
  for fidx, file_path in enumerate(files):
    print(f"{fidx + 1}/{nfiles} {file_path.name}")
    if not file_path.is_file():
      continue

    with file_path.open("r") as f:
      submission = f.read()
    
    name = file_path.name
    ext = file_path.suffix[1:]
    id = name.split("_")[0]
    data = API.get_problem(id)
    if data is None:
      print(f"Failed to get problem {id}")

    items = data.get("items", [])
    if len(items) != 1:
      print(f"Problem id {id} has no unique item: {items}")
      continue
    
    item = items[0]
    level = item.get("level", -1)
    titles = dict([lang.get('language', '<unknown>'), lang] for lang in item.get("titles", []))

    title_lang = ''
    if 'ko' in titles:
      title_lang = 'ko'
    if 'en' in titles:
      title_lang = 'en'
    if title_lang == '':
      print(f"No title in English or Korean for problem {id} titles: {titles}")
      continue

    title = titles[title_lang].get("title", "<unknown>")
    tier = get_tier(level)
    tier_pretty = f"{tier[:-1].capitalize()} {tier[-1]}" if tier != "unrated" else "Unrated"
    path = Path(f"./tiers/{tier}/{secure_filename(id)}_{secure_filename(title)}.{ext}")
    Path.mkdir(path.parent, exist_ok=True, parents=True)
    with path.open("w", encoding="utf-8") as f:
      if ext == "py":
        f.write(f"\"\"\"")
      else:
        f.write(f"/*\n")
      f.write(f"{tier_pretty}\n{id} - {title}\nmeta: {json.dumps(item, ensure_ascii=False)}\n")
      if ext == "py":
        f.write(f"\"\"\"\n\n")
      else:
        f.write(f"*/\n\n")
      f.write(f"{submission}")

if __name__ == "__main__":
  main()
    