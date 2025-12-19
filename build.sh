#!/bin/env bash
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

# Get directory of script itself
SOURCE="${BASH_SOURCE[0]}"
# resolve $SOURCE until the file is no longer a symlink
while [ -h "$SOURCE" ]; do
    DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"
    SOURCE="$(readlink "$SOURCE")"
    # if $SOURCE was a relative symlink, we need to resolve it relative to the
    # path where the symlink file was located
    [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE"
done
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"

mkdir -p $DIR/build $DIR/images

docker build --tag zephyr_dev $DIR/docker
docker run \
    --rm \
    -it \
    -v $DIR:/app/project/app:Z \
    -v $DIR/build:/app/project:Z \
    -v $DIR/docker/entrypoint.sh:/app/entrypoint.sh:ro,Z \
    -v $DIR/images:/app/images:Z \
    -t zephyr_dev
