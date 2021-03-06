
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssacrist </var/mail/ssacrist>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/10 09:30:55 by ssacrist          #+#    #+#              #
#    Updated: 2020/09/17 03:01:59 by ssacrist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -g get_next_line.c gnl_main.c -o get_next_line
./get_next_line < get_next_line.c > yours_.res
cat -e yours_.res > yours.res
cat -e < get_next_line.c > original.res
diff -y --suppress-common-line original.res yours.res
rm -rf original.res yours_.res yours.res get_next_line