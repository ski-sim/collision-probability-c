# 50분소요 
import json
import requests
import configparser
import time
import schedule
import time
import datetime
import csv

DISCOS_URL = 'https://discosweb.esoc.esa.int'
DISCOS_TOKEN = 'Ijk1YjRjMWYwLTc1ZDItNDc4NS04MzQ4LTgyZmM3MDk2M2IyYiI.lqet3mWHZooxHwUGaRqLBOTvYjI'
DISCOS_SATNO_MAX = 9223372036854775807	#9223372036854775807
DISCOS_PAGE_SIZE_MAX = 100

uriBase = "https://www.space-track.org"
requestLogin = "/ajaxauth/login"
requestCmdAction = "/basicspacedata/query"
requestFindObjects =f"/class/tle_latest/NORAD_CAT_ID/<{DISCOS_SATNO_MAX+1}/ORDINAL/1/format/json/orderby/NORAD_CAT_ID%20asc"


def get_discos_tle_objects(SATNO_CHUNK_STR):
    response = requests.get(
        f'{DISCOS_URL}/api/objects',
        headers={
            'Authorization': f'Bearer {DISCOS_TOKEN}',
            'DiscosWeb-Api-Version': '2',
        },
        params={
            'filter': f'in(satno,{SATNO_CHUNK_STR})',
            'page[size]': f'{DISCOS_PAGE_SIZE_MAX}',
            'sort': 'satno',            
        }
    )
    doc = response.json()
    DISCOS_OBJECTS = doc['data']
    return DISCOS_OBJECTS

def get_tle_full_catalog():

    # set of satellite ids of objects included in TLE data
    SATNO_LIST = []

    # Use configparser package to pull in the ini file (pip install configparser)
    config = configparser.ConfigParser()
    config.read("./Login.ini")
    configUsr = config.get("configuration", "username")
    configPwd = config.get("configuration", "password")
    siteCred = {'identity': configUsr, 'password': configPwd}

    with requests.Session() as session:
        # run the session in a with block to force session to close if we exit

        # need to log in first. note that we get a 200 to say the web site got the data, not that we are logged in
        response = session.post(uriBase + requestLogin, data=siteCred)
        if response.status_code != 200:
            print("Error, POST fail on login")

        # this query picks up objects from the catalog. Note - a 401 failure shows you have bad credentials
        response = session.get(uriBase + requestCmdAction + requestFindObjects)
      
        if response.status_code != 200:
            print("Error, GET fail on request")

        data = json.loads(response.text)
        
        for object in data:
            SATNO = object['NORAD_CAT_ID']
            SATNO_LIST.append(SATNO)

        session.close()

    return SATNO_LIST

def create_dimension_txt():
    current_time = datetime.datetime.now().strftime("%Y_%m_%dT%H_%M_%S")
    SATNO_LIST = get_tle_full_catalog()
    SATNO_LIST_CHUNK = [
        SATNO_LIST[i:i+DISCOS_PAGE_SIZE_MAX] 
        for i in range(0, len(SATNO_LIST), DISCOS_PAGE_SIZE_MAX)
    ]
    count=0  
    obj_dict = dict()
    for idx, chk in enumerate(SATNO_LIST_CHUNK):
        print(f'chk:{chk}')
        
        SATNO_CHUNK_STR = '(' + ','.join(chk) + ')'

        DISCOS_OBJECTS = get_discos_tle_objects(SATNO_CHUNK_STR)
        for obj in DISCOS_OBJECTS:
            
            obj_dict[obj['attributes']['satno']] = obj['attributes']
            if (count + 1) % 19 == 0:
                print(f'{count}th sleep')
                time.sleep(61)
                count+=1
        count+=1  
    dimension_path = f'./dimension/{current_time}.txt'

    # Writing JSON data
    with open(dimension_path, 'w') as f:
        json.dump(obj_dict, f, indent='\t')
    return current_time, dimension_path

def convert_to_csv(current_time, dimension_txt_file_path):

    with open(dimension_txt_file_path, "r") as file:
        size_dic = json.load(file)

    dimension_csv_file_path = f'./dimension/{current_time}.csv'

    # CSV 파일 작성
    with open(dimension_csv_file_path, 'w', newline='', encoding='utf-8') as csvfile:
        column_names = size_dic['4'].keys()  # 첫 번째 항목의 키들을 필드로 사용
        print(column_names)
        writer = csv.DictWriter(csvfile, fieldnames=column_names)

        # CSV 파일 헤더 작성
        writer.writeheader()

        # 딕셔너리 데이터를 CSV 파일로 작성
        for key, value in size_dic.items():
            if 'name' in value and value['name'] is not None:
                value['name'] = value['name'].replace(',', '.')  # 'name' 필드의 쉼표를 마침표로 변경   
            writer.writerow(value)