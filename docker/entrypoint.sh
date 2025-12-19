#!/bin/bash
 ##############################################################################
 #                                                                            #
 # Copyright (C) 2025 Nils Bosbach                                            #
 # All Rights Reserved                                                        #
 #                                                                            #
 # This is work is licensed under the terms described in the LICENSE file     #
 # found in the root directory of this source tree.                           #
 #                                                                            #
 ##############################################################################

set -e

cd /app/project

if [ -d "/app/project/.venv" ] && [ "$(ls -A "/app/project/.venv")" ]; then
    echo "venv found - activating"

    source /app/project/.venv/bin/activate
    west update
else
    echo "creating venv"

    python3 -m venv /app/project/.venv
    source /app/project/.venv/bin/activate

    pip3 install wheel west

    west init -l /app/project/app
    west update

    pip3 install -r /app/project/zephyr/scripts/requirements.txt
fi

cd /app/project/app

image_dir=/app/images
tmp_image_dir=/app/project/tmp_images
cores=(1 2 4 8)
apps=()
for dir in app/*/; do
    apps+=("$(basename "$dir")")
done
mkdir -p ${tmp_image_dir}

for app in ${apps[@]}; do
    mkdir -p ${tmp_image_dir}/${app}
    sed -e "s/%NAME%/${app}/g" /app/project/app/vp_config/zephyr.cfg >  ${tmp_image_dir}/${app}/${app}.cfg

    for core in "${cores[@]}"; do
        build_dir=/app/project/build/${app}x${core}
        mkdir -p ${build_dir}
        west build -b avp64/avp64/x${core} app/${app} -d ${build_dir} -- -DSOC_ROOT="$PWD" -DBOARD_ROOT="$PWD"

        cp ${build_dir}/zephyr/zephyr.bin ${tmp_image_dir}/${app}/${app}x${core}.bin
        cp ${build_dir}/zephyr/zephyr.elf ${tmp_image_dir}/${app}/${app}x${core}.elf

        cfg_file="system.desc = Boots ${app} on a ${core}-core AVP64\n"
        cfg_file+="system.cpu.ncores = ${core}\n"
        cfg_file+="%include \${dir}/${app}/${app}.cfg\n"
        echo -e "${cfg_file}" > ${tmp_image_dir}/${app}x${core}.cfg
    done
    tar -czf ${image_dir}/${app}.tar.gz -C ${tmp_image_dir} .
    rm -rf ${tmp_image_dir}/*
done
