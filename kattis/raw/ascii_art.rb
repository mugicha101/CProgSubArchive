# 2026-08-01 13:25:18 
m = gets.chomp.match(/^\s*What\s+is\s+problem\s+(?<pid>[A-C])\s+about\?\s*$/)
if m.nil?
  puts 'I am not sure how to answer that.'
  exit
end
case m[:pid]
when 'A'
  puts 'Problem A is about Ascii Art
   _     __   __  _   _
  / \   / /  / / | | | |
 / _ \  \ \ | |  | | | |
/_/ \_\ /_/  \_\ |_| |_|
'
when 'B'
  puts 'Problem B is about Fortnite
###############
###############
####       /###
####   ########
####       ####
####   ########
####   ########
####   ########
####_~<########
###############
'
when 'C'
  puts 'Problem C is about The Legend of Zelda
     /\
    /  \
   /____\
  /\    /\
 /  \  /  \
/____\/____\
'
else
  puts 'I am not sure how to answer that.'
end