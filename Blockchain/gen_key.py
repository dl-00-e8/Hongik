import ecdsa
import hashlib

# 개인 키 생성
private_key = ecdsa.SigningKey.generate(curve=ecdsa.SECP256k1)

# 개인 키를 16진수 문자열로 변환
private_key_hex = private_key.to_string().hex()
print("Private Key:", private_key_hex)

# 비압축 공개 키 생성
public_key = private_key.get_verifying_key()

# 공개 키 압축
def compress_public_key(public_key):
    x = public_key.pubkey.point.x()
    y = public_key.pubkey.point.y()
    prefix = '02' if y % 2 == 0 else '03'
    return prefix + format(x, '064x')

compressed_public_key_hex = compress_public_key(public_key)
print("Compressed Public Key:", compressed_public_key_hex)

# 공개 키 해시 생성
def get_pubkey_hash(pubkey_hex):
    # SHA256 해시
    sha256_hashed = hashlib.sha256(bytes.fromhex(pubkey_hex)).digest()
    # RIPEMD160 해시
    ripemd160_hashed = hashlib.new('ripemd160', sha256_hashed).hexdigest()
    return ripemd160_hashed

pubkey_hash = get_pubkey_hash(compressed_public_key_hex)
print("Public Key Hash:", pubkey_hash)

# 결과 출력
# print("Private Key:", private_key_hex)
# print("Public Key:", compressed_public_key_hex)
# print("Public Key Hash:", pubkey_hash)

vk = ecdsa.VerifyingKey.from_string(bytes.fromhex(compressed_public_key_hex), curve=ecdsa.SECP256k1)
print(vk)
is_valid = vk.verify(bytes.fromhex(private_key_hex), bytes.fromhex(private_key_hex))
print(is_valid)