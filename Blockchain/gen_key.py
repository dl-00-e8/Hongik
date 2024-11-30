import ecdsa
import hashlib

# 개인 키 생성
private_key = ecdsa.SigningKey.generate(curve=ecdsa.SECP256k1)

# 개인 키를 16진수 문자열로 변환
private_key_hex = private_key.to_string().hex()

# 개인 키로부터 공개 키 생성
public_key = private_key.get_verifying_key()

# 공개 키를 16진수 문자열로 변환
public_key_hex = public_key.to_string().hex()

# 공개 키 해시 생성
def get_pubkey_hash(pubkey_hex):
    # SHA256 해시
    sha256_hashed = hashlib.sha256(bytes.fromhex(pubkey_hex)).digest()
    # RIPEMD160 해시
    ripemd160_hashed = hashlib.new('ripemd160', sha256_hashed).hexdigest()
    return ripemd160_hashed

# 공개 키 해시 생성
pubkey_hash = get_pubkey_hash(public_key_hex)

# 결과 출력
print("Private Key:", private_key_hex)
print("Public Key:", public_key_hex)
print("Public Key Hash:", pubkey_hash)