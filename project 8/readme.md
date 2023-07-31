## **Project8**: **AES** impl with **ARM** instruction
**一、概述**
这段代码是在ARMv8架构上使用AES内部函数进行AES加密和解密操作，并利用ARMv8的AES扩展指令来优化AES算法的执行。通过使用C内部函数，可以更方便地访问这些指令，以实现更高效的加密和解密功能。

在ARM架构的SIMD（单指令多数据）指令集中，AESE（AES single round encryption）表示AES的单轮加密操作，其中包括AddRoundKey、SubBytes和ShiftRows。
**二、指令集文档**
通过指令集文档（https://developer.arm.com/architectures/instruction-sets/intrinsics/#q=AES）可以查到以下用于执行AES操作的函数定义：

// 执行AES单轮加密  
uint8x16_t vaeseq_u8(uint8x16_t data, uint8x16_t key);

// 执行AES混淆列操作  
uint8x16_t vaesmcq_u8(uint8x16_t data);

上述函数可以利用ARMv8架构的硬件加速器来执行AES加密和解密操作，从而实现更高效的数据处理。
