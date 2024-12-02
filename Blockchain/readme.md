# 블록체인 프로그래밍 프로젝트

### 개요
Execution Engine을 GUI 기반으로 동작할 수 있도록 구현한 프로젝트

### 실행 방법
`python3 full_node.py` 또는 `python full_node.py `

### 사용 방법
1. Execution Engine 실행
최상단에 위치한 ‘Execution Engine 실행’ 버튼을 클릭하여 Transaction 을 처리하는 과정을 진행할 수 있습니다. Transaction 이 처리될 때마다, 그 결과가 버튼 아래의 Text 보드에 출력됩니다. (다만, 실행 엔진의 스크립트 처리 속도가 빠르기에 결과를 누적으로 출력하는 방식으로 구현되어 있습니다.)

2. Query Process 확인
Execution Engine 실행 중, ‘Query Process 확인’ 버튼을 클릭하여 Transaction 처리 중 현재의 UTXO 집합과 현재까지 처리된 트랜잭션들의 성공/실패 여부를 확인할 수 있습니다. 첫 번째
Table 이 UTXO 집합을 출력하며, 두 번째 Table 이 처리된 Transaction 들의 정보를 나타냅니다.

### 주요 파일 정보
개발한 파일 및 관련 정보는 다음과 같습니다.

- full_node.py: 실행 엔진의 핵심 비즈니스 로직 및 GUI 설정이 개발되어 있습니다. 주요 기능들은 해당 파일에 작성된 코드로 동작합니다.
- gen_key.py: private key, public key 를 생성합니다. 이에 더해, signature, public key hash 등의 정보를 생성할 수 있습니다. 이는 트랜잭션에서 checksig, checkmultisig 등과 같은 연산을 처리하는데 활용됩니다.
- hash.py: scriptX 를 hash 한, scriptXhash 를 생성하기 위한 스크립트입니다.
- key_1, key_2, key_3: gen_key.py 로 생성한 정보들입니다.
- transaction.json: 실행 엔진 최초 시작 시, 가지고 있는 transaction 정보들을 json 형식으로 가지고 있습니다. 현재는 P2PKH, P2SH, Multisig 등 총 3 가지 유형에 대한 transaction 을 가지고 있습니다.
- utxoes.json: 실행 엔진 최초 시작 시, 가지고 있는 UTXO 정보들을 json 형식으로 가지고 있습니다. Transaction 에서 사용하는 UTXO 정보들을 동일하게 가지고 있습니다.

### 사용한 라이브러리
- re: 정규표현식으로, unlocking script + locking script 를 stack-based 로 실행하기 위해 리스트로 변환 시 사용
- sys:PyQt의GUI종료시활용
- json: json 형식의 transaction, utxo 파싱을 위해 사용
- dataclass: transaction, utxo 데이터 형식 정의를 위해 사용
- hashlib: SHA256, RIPEMD160 등으 암호화를 위해 사용
- ecdsa:서명생성및검증과정을위해사용
- PyQt5: GUI 로 시각화하기 위해 사용
 
### 실행엔진 세부 구현 정보
1. 파일 실행 시
- PyQt5 라는 라이브러리를 활용하여 GUI 를 구성합니다.
- 실행엔진은 동일한 디렉토리 내의 json 파일로부터 데이터를 불러와 초기화됩니다.
- UTXO 리스트와 Transaction 리스트는 각각 별도의 데이터 파일에서 로드됩니다.
- UTXO 파일은 사용되지 않은 트랜잭션 출력(Unspent Transaction Outputs)을 저장하며, 초기
블록체인 상태를 구성합니다.
- Transaction 파일은 과거의 모든 트랜잭션 기록을 담고 있어 트랜잭션 검증 및 블록 생성에
사용됩니다.
- 이 파일 데이터들은, List 형태의 자료구조로 엔진 내부에 저장되어 있습니다.

2. 엔진 실행 시
-  트랜잭션 검증
    - 제출된 트랜잭션이 UTXO 리스트와 일치하는지 확인합니다.
    - 서명 검증 및 스크립트 실행을 통해 트랜잭션의 유효성을 검증합니다.
        - ecdsa 라는 암호화 라이브러리를 활용하여 signature 와 public key 간 유효성을 검증합니다. 서명 검증 시, 필요한 메시지는 txid 를 활용하는 방식으로 구현했습니다.
        - 스크립트의 형태로 데이터가 들어오게 되므로, 검증하는 과정을 stack-based 로 구현했습니다.
        - Unlocking script 와 Locking scrip 에서 각 operator 및 operand 를 명확하게 구분하기 위하여 ‘|’를 구분자로 사용했습니다. |를 구분자로 사용한 이유는 스크립트 자체가 하나의 operand 로 들어오는 경우 구분이 불가능하기 때문에 활용했습니다.
        - Multisig 의 경우, M*N 개의 경우의 수를 모두 검증하는 이중 반복문을 진행하면서 검증에 성공한 횟수를 기록합니다. 검증에 성공한 횟수가 M 과 동일한 경우 성공으로 간주합니다.
-  UTXO 업데이트
    - 사용된 UTXO 는 리스트에서 제거되고, 새로운 UTXO 가 추가됩니다.
- Transaction 기록
    - 검증된 트랜잭션은 내부 Transaction 리스트에 추가됩니다.
- Transaction 결과 출력
    - Transaction 의 성공/실패 여부와 상관없이 GUI 의 Text 보드에 결과를 출력합니다.

3. Query Process 확인
- 최초 파일 실행 시, 저장된 UTXO 리스트 및 검증된 트랜잭션을 저장하고 있는 내부 Transaction 리스트를 가져와 GUI 의 Table 에 출력합니다.
 