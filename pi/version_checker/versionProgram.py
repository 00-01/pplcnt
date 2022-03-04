import argparse
import json
import os
import shutil
import time

import requests as requests

print('구버전임')
print('pid', os.getpid())

# add following to cron
# @reboot version_checker.py >> log/version_checker.log

configFile = 'versionConfig.json'
serverURL = 'https://115.68.37.86.8180/version'    # data url

uuid = '1234'

config = dict()
config['version'] = 0.0

parser = argparse.ArgumentParser(description='versionProgram')
parser.add_argument('-n', '--new', type=int)
args = parser.parse_args()

updateVersion = args.new

# 새로운 파일 다운로드 된거임
if updateVersion is not None:
    # 파일 카피해서 복사하고 옆에놈 실행하고 자기는 종료해야됨
    time.sleep(1)
    shutil.copy('versionProgram1.py', 'versionProgram.py')
    os.system('versionProgram.py')
    # 리눅스는 pkill임 (소스다름)
    # 윈도우는 관리자권한아니면 종료안됨
    os.system(f'taskkill /f /pid {os.getpid()}')
    exit()
    pass
else:
    if os.path.exists('versionProgram1.py'):
        os.remove('versionProgram1.py')

if not os.path.exists(configFile):
    with open(configFile, 'w') as f:
        json.dump(config, f, indent='\t')
else:
    with open(configFile, 'r') as f:
        config = json.load(f)

js = '''{
  "version": 1.1,
  "file": [
    {
      "url":"http://asdfasdf.net",
      "fileName":"versionProgram.py",
      "fileSize":3250
    },
    
  ]
}'''

'''
{
      "url":"http://asdfasdf.net",
      "fileName":"versionProgram123123.py",
      "fileSize":32505
    }
'''


def checkFileSize(fileName):
    return os.path.getsize(fileName)


params = {'uuid': uuid}
# 서버에 버전프로그램 버전 몇인지 요청
response = requests.get(serverURL, params=params)
serverVersion = 1.1

# 서버와 버전 다르면
if config['version'] != serverVersion:
    # 디렉토리에 있는 파일들 중 버전프로그램 빼고 전체 삭제함
    for fileList in os.listdir():
        if fileList == '.idea' or fileList == 'versionProgram.py' or fileList == configFile:
            continue
        else:
            os.remove(fileList)

    # js = resopnse값 설정해야됨-------------------------------------------------------------
    # 현재 js는 테스트값임
    p = json.loads(js)
    fileIndex = 0
    while fileIndex < len(p['file']):
        k = 10
        fileURL = p['file'][fileIndex]['url']
        fileName = p['file'][fileIndex]['fileName']

        # 파일 데이터 요청(주석풀어야됨)
        # downloadFile = requests.get(fileURL + '/' + fileName, allow_redirects=True)
        if fileName == 'versionProgram.py':
            # 버전프로그램 다운로드 뒤에 1추가해서 저장
            # 파일 저장(주석풀어야됨)
            # open('versionProgram1.py', 'wb').write(downloadFile.content)
            pass
        else:
            # 파일 저장(주석풀어야됨)
            # open(fileName, 'wb').write(downloadFile.content)
            pass
        k = 10
        downloadFileSize = checkFileSize(fileName)
        # 파일 무결성 검증(주석풀어야됨)
        # if downloadFileSize != p['file'][fileIndex]['fileSize']:
        #     print(fileName, 'size error server : ', p['file'][fileIndex]['fileSize'], 'download : ', downloadFileSize)
        #     #여러번 틀리면 재부팅할지 추가하십셔
        #     continue
        fileIndex += 1
    k = 10

    # 파일 다운로드 다 끝나면 config에 버전값 수정
    config['version'] = serverVersion
    with open(configFile, 'w') as f:
        json.dump(config, f, indent='\t')

    # versionProgram1실행하고 파라미터 --new 1 주고 자기는 죽음
    os.system('versionProgram1.py --new 1')
    # 리눅스는 pkill임 (소스다름)
    # 윈도우는 관리자권한아니면 종료안됨
    os.system('taskkill /f /pid ' + os.getpid())
    exit()

# -------------------------------------------------버전 종료-----------------------------------
# window는 process다죽는거 확인했는데 linux계열은 테스트해봐야됨pkill로 할거면 pid저장해서 처리해야됨

# 프로그램버전이랑 서버 버전이 동일할때 할일 체크
# 프로그램 켜고

while True:
    time.sleep(1)
k = 10

# response.json()

while True:
    # 버전 체크 요청
    # 버전 체크
    # 분기 1. 2. 중 선택
    # 1. 버전 다르면 컴퓨터 재부팅하던지
    # 2. versionProgram1 복사해서 --new 1 파라미터줘서 다시 재시작하던지

    # 버전 체크 완료됬음
    # 서버에서 명령어 던졌는지 체크
    # 있으면 os.system으로 돌리면됨

    time.sleep(1)
