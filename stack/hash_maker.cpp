int hash_maker(int password){

    static int64_t passwordArray[5] = 0;

    static int funcStartedTimes = 0;

    if(funcStartedTimes < 5){

        passwordArray[funcStartedTimes] = password;

    }

    //if

}
