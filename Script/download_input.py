import requests
import time
import os


def fetch_input_data(day):
    year = 2024
    print(f"fetching input data for day:{day:02} , year: {year}")
    session_cookie = "53616c7465645f5f82eb2a130147026a21a12b32d641ea6d6717d623b63fdf38d8518ff55feee89b724d72c954c203a56c6cacc661a19eef3ba62fd35599e403"
    url = f"https://adventofcode.com/{year}/day/{day}/input"

    #check if the path has a size > 0 OR  even exists OR has the same text i want to copy in
    input_path = f"C:/Users/anblo/Documents/CodingProjects/AoC_Uni/inputs/day{day:02}.txt"
    example_path = f"C:/Users/anblo/Documents/CodingProjects/AoC_Uni/inputs/day{day:02}_example.txt"
    #input_path = f"A/inputs/day{day:02}.txt"
    if os.path.exists(input_path):
        print(f"input txt file for day {day:02} already exists! want to continue anyway? .....")
        ans = input("y/n:  ")
        if ans!="Y":
            print("exiting...")
            return
    

    response = requests.get(url, cookies={"session": session_cookie})
    if response.ok:
        #print("session ok!")
        with open(input_path, "w") as file:
            file.write(response.text)
    else:
        print("session failed!")

    with open(example_path, "w") as exFile:
        exFile.write("")


if __name__ == "__main__":
    import sys
    argv = sys.argv
    argc = len(argv)

    if argc > 1:
        if argv[1].lower() == "help":
            print(" specify day!")
        day = int(argv[1])
        if day < 25 and day > 0:
            fetch_input_data(day)
        else:
            print("day must be between 0 and 25")