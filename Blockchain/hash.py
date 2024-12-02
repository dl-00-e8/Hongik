import hashlib

def hash160(script):
    # 스크립트를 바이트 형식으로 변환
    script_bytes = script.encode('utf-8')  # 전체 스크립트를 UTF-8로 인코딩

    # SHA-256 해시
    sha256_hashed = hashlib.sha256(script_bytes).digest()
    print(sha256_hashed)
    # RIPEMD-160 해시
    ripemd160_hashed = hashlib.new('ripemd160', sha256_hashed).digest()
    
    return ripemd160_hashed

# 주어진 스크립트
script = "02359cab35e02e92a9b12e24f1aa57256f8045c866cbbbeedada704a18d97efc0d OP_CHECKSIG"

# HASH160 계산
hashed_value = hash160(script)

# 결과 출력
print("HASH160:", hashed_value.hex())