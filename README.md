# markovs_text_chain
Markovs chain text generator nth order

Description: reads data from incoming urls & generate text based on learned part

Requires: libcurl-devel

usage:
run 
**learner --urls ./../test_urls/tu1.txt --chaincount 2 --mcdump ./tutest_dump.txt**
it will run learner, which process all text in urls file, 
build markovs chain with count and save result to dump file

run 
**text_generator --chainsequence 5 --mcdump ./tutest_dump.txt --phrase "exist"** 