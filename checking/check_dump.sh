if [ $# -eq 0 ]
  then
	  echo "usage:"
	  echo "./check_dump.sh champ1.cor champ2.cor [num of cycles before dump]"
	exit 1
fi

./corewar -d ${@:$#} ${@:1:$#-1} > mine
./vm_champs/corewar -d ${@:$#} ${@:1:$#-1} > need

diff mine need > res

cat res
