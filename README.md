# how to complie project
`gcc -o app main.c project.c`
# how to complie the unit test
`gcc -o test_app test.c project.c`
# how to compile the E2E test
`gcc -o test_e2e e2e.c project.c maine2e.c`
# how to run app , unit test , E2E test
`./app`
`./test_app`
`./test_e2e`