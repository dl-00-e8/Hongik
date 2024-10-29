-- like 버전
SELECT cname, age, grade, savings
FROM client
where cname like '김%'

-- substring 버전
SELECT cname, age, grade, savings
FROM client
where SUBSTR(cname, 0, 1) = '김'

SELECT cname, age, grade, savings
FROM client
where SUBSTR(cname, 1, 1) = '김'