while True:
  x, y = [ int(x) for x in input().split() ]
  if x == 0 and y == 0:
    break
  print(x+y)
