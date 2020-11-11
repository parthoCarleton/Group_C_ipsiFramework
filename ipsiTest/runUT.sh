#!bash


echo "*********************************************************"
echo "**Unit Test Case START**"
echo "*********************************************************"
cd ut_test
mkdir bin
make

for ut in bin/*.ut; 
do
	if(./"$ut")
	then
		echo " "
	else
		echo "ABORT"
		exit
		break;
	fi
done
echo "*********************************************************"
echo "**Unit Test Case END**"
echo "*********************************************************"

echo "*********************************************************"
echo "**Code Coverage START**"
echo "*********************************************************"

mv *.gcno bin/
mv *.gcda bin/

for gcda in bin/*.gcda;
do
	gcov "$gcda"
done

lcov -c --directory . --output-file main_coverage.info
lcov -r  main_coverage.info "*_UT.c" -o main_coverage.info
lcov -r  main_coverage.info "*_UT.hpp" -o main_coverage.info

genhtml main_coverage.info --output-directory ../report

rm *.gcov
rm *.info
rm -rf bin
cd ../
echo "*********************************************************"
echo "**Code Coverage END**"
echo "*********************************************************"
echo "*********************************************************"
echo "**UT completed , See the coverage data in report folder**"
echo "*********************************************************"
