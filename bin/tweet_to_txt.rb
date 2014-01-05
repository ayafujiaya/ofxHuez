# -*- coding: utf-8 -*-
require 'oauth'
require 'JSON'
require 'uri'



path_to_txt = "/Users/Yuki/work/ofxHuez/search_result.txt"

class TwitterConnects

@@CONSUMER_KEY = ''
@@CONSUMER_SECRET = ''
@@ACCESS_TOKEN = ''
@@ACCESS_TOKEN_SECRET = ''

def getTweets(encodedQuery) 
  consumer = OAuth::Consumer.new(
    @@CONSUMER_KEY,
    @@CONSUMER_SECRET,
    :site => 'http://twitter.com'
    )

  access_token = OAuth::AccessToken.new(
    consumer,
    @@ACCESS_TOKEN,
    @@ACCESS_TOKEN_SECRET
  )

requestAPIURL = 'http://api.twitter.com/1.1/search/tweets.json?q=' + encodedQuery

url_escape = URI.escape(requestAPIURL)
response = access_token.get(url_escape)

JSON.parse(response.body).each do |status|
  status.each do |items|
  if (items.instance_of?(Array))
    items.each do |statusesItems|
    if (statusesItems.instance_of?(Hash))
      open(path_to_txt, "a") {|f| f.write(statusesItems['text'] + "\n")}
      puts statusesItems['text']
    end
  end
end
end
end
end
end


hoge = TwitterConnects.new
puts "type search text!!"
searchText = gets()

while(true) do
  puts "--------------------------------"
  open(path_to_txt, "w") {|f| f.write('')}
  open(path_to_txt, "a") {|f| f.write(searchText)}
  hoge.getTweets(searchText)  
  puts "--------------------------------"
  sleep(30)
end
