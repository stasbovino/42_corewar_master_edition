.name "op_ld"
.comment "ld T_DIR/T_IND, T_REG, delay 5, загружает значение в регистр, меняет carry"

ld %5, r2
st r2, 40
ld -1, r3
st r3, 80
