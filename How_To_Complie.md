# Use ubuntu or linux to compile and Running
# how to complie project
`gcc -o app main.c project.c`
# how to complie the unit test
`gcc -o unit_test test.c project.c`
# how to compile the E2E test
`gcc -o E2E_test e2e.c project.c maine2e.c`
# how to run app , unit test , E2E test
`./app`