# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    input_tests.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/05 16:49:25 by jcesar-s          #+#    #+#              #
#    Updated: 2025/08/05 17:12:33 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

echo "Testing 3 args (Expecting exit code equals to 1)"
$1 maps/japan.fdf julio
echo "exit code: $?\n"

echo "Testing 1 arg (Expecting exit code equals to 1)"
$1 
echo "exit code: $?\n"

echo "Testing 2 args (Expecting no exit code equals to 1)"
$1 maps/japan.fdf
echo "exit code: $?\n"

# Filetype
echo "Testing valid file (Expecting no exit code equals to 2)"
$1 file.fdf
echo "exit code: $?\n"

echo "Testing file.fdf.pdf (Expecting exit code equals to 2)"
$1 file.fdf.pdf
echo "exit code: $?\n"

echo "Testing file.fdf.pdf (Expecting exit code equals to 2)"
$1 .fdffile
echo "exit code: $?\n"

echo "Testing file.fdf.pdf (Expecting exit code equals to 2)"
$1 file.txt
echo "exit code: $?\n"

