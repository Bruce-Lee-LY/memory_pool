# Copyright 2022. All Rights Reserved.
# Author: Bruce-Lee-LY
# Date: 23:24:29 on Sun, May 22, 2022
#
# Description: run sample script

#!/bin/bash

set -euo pipefail

WORK_PATH=$(cd $(dirname $0) && pwd) && cd $WORK_PATH

rm -rf log && mkdir -p log/sample

nohup $WORK_PATH/output/sample/mp_sample > log/sample/mp_sample.log 2>&1 &
