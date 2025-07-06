// See https://aka.ms/new-console-template for more information
using System;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Threading.Tasks;
using Microsoft.VisualBasic;

Console.WriteLine("Hello, World!");


int day = 5;
int year = 2024;
int part = 1;
string session_cookie = "53616c7465645f5f82eb2a130147026a21a12b32d641ea6d6717d623b63fdf38d8518ff55feee89b724d72c954c203a56c6cacc661a19eef3ba62fd35599e403";
string answer = "123456";

var client = new HttpClient();
client.DefaultRequestHeaders.Add("User-Agent", "AoC submitter by Snushakan");

var content = new FormUrlEncodedContent(new[]
{
    new KeyValuePair<string,string>("level", part.ToString()),
    new KeyValuePair<string, string>("answer", answer)
});

client.DefaultRequestHeaders.Add("Cookie", session_cookie);

var url = $"https://adventofcode.com/{year}/day/{day}/answer";
var response = await client.PostAsync(url, content);

var response_text = await response.Content.ReadAsStringAsync();

if (response.IsSuccessStatusCode)
{
    Console.WriteLine("Success!!!! \n");
    Console.WriteLine(response_text);
}