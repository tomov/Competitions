@echo off
del perm.in
echo 1 >> perm.in
echo %1 >> perm.in
echo %2 >> perm.in

echo ---perm.in---
type perm.in

perm < perm.in > out

del perm.in
echo 2 >> perm.in
echo %1 >> perm.in
type out >> perm.in

echo ---perm.in----
type perm.in

perm < perm.in > xout

echo -xout----
type xout

