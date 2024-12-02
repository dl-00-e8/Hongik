import ecdsa
import hashlib

# 개인 키와 압축된 공개 키 생성
private_key = ecdsa.SigningKey.generate(curve=ecdsa.SECP256k1)
public_key = private_key.get_verifying_key()
compressed_public_key = public_key.to_string("compressed")

# 압축된 공개 키를 16진수 문자열로 변환
compressed_public_key_hex = compressed_public_key.hex()

# 메시지
message = b"1122334455"
# 메시지 해시
message_hash = hashlib.sha256(message).digest()

# 서명 생성
signature = private_key.sign(message_hash)
signature_hex = signature.hex()

# 서명 검증
def verify_signature(compressed_pub_key, message, signature):
    # 압축된 공개 키로부터 공개 키 복원
    vk = ecdsa.VerifyingKey.from_string(bytes.fromhex(compressed_pub_key), curve=ecdsa.SECP256k1)
    
    # 메시지 해시
    message_hash = hashlib.sha256(message).digest()
    
    # 서명 검증
    return vk.verify(signature, message_hash)

# SHA256 해시
sha256_hashed = hashlib.sha256(bytes.fromhex(compressed_public_key_hex)).digest()
    # RIPEMD160 해시
ripemd160_hashed = hashlib.new('ripemd160', sha256_hashed).hexdigest()
print("Pubkey hash: " + ripemd160_hashed)

# 서명 검증 호출
is_valid = verify_signature(compressed_public_key_hex, message, signature)

print("Signature: ", signature_hex)
print("Compressed Public Key (Hex):", compressed_public_key_hex)
print("Is the signature valid?", is_valid)