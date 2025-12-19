#!/bin/env bash
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
