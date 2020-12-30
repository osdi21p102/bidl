#!/bin/bash
docker stop $(docker ps -aq --filter name="bft")
docker rm $(docker ps -aq --filter name="bft")