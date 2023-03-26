#!/bin/bash

deploy () {
    username=carson
    server_ip=167.224.158.29
    remote_dir=/programs
    exe_path=$(pwd)/bin/grackle
    
    if [ ! -f "$exe_path" ]; then # check if file exists
        echo $exe_path does not exist, failed
        exit 1
    fi

    #connect with ssh and kill currently running server

    ssh $username@$server_ip "
        pkill -9 grackle
        exit
    "
    if [ ! $? -eq 0 ]; then
        exit 2
    fi

    #copy over the new server exe
    scp $exe_path $username@$server_ip:$remote_dir
    if [ ! $? -eq 0 ]; then
        exit 3
    fi

    #run the server in the background
    ssh $username@$server_ip "
        cd $remote_dir
        ./grackle </dev/null >/dev/null 2>&1 &
        exit
    "
    if [ ! $? -eq 0 ]; then
        exit 4
    fi
}

echo Deploying Grackle build

deploy

echo Grackle deployed successfully

# check if grackle exits
# kill the application on the server
# scp to the server /programs
# launch the program in the background