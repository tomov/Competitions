@echo off

echo TEST 1
echo 5 3 >cups.in
echo 5 3 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 2
echo 3 5 >cups.in
echo 3 5 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 3
echo 5 6 >cups.in
echo 5 6 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 4
echo 6 8 >cups.in
echo 6 8 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 5
echo 9 4 >cups.in
echo 9 4 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 6
echo 8 7 >cups.in
echo 8 7 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 7
echo 8 9 >cups.in
echo 8 9 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 8
echo 9 10 >cups.in
echo 9 10 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 9
echo 10 9 >cups.in
echo 10 9 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

echo TEST 10
echo 10 10 >cups.in
echo 10 10 >cups.out
showtime >time.txt
cups <cups.in >>cups.out
showtime >>time.txt
calctime
tcups <cups.out
pause

del cups.in
del cups.out
del time.txt
