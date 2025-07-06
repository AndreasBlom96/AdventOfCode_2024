import requests
import time

day = 7
year = 2024

session_cookie = "53616c7465645f5f82eb2a130147026a21a12b32d641ea6d6717d623b63fdf38d8518ff55feee89b724d72c954c203a56c6cacc661a19eef3ba62fd35599e403"
url = f"https://adventofcode.com/{year}/day/{day}/input"

response = requests.get(url, cookies={"session": session_cookie})

if response.ok:
    #write code here
    print("session ok!")
    with open(f"inputs/day{day:02}.txt", "w") as file:
        file.write(response.text)
else:
    print("session failed!") 