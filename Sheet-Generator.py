import os
import time
import selenium
from dotenv import load_dotenv
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait

load_dotenv()

def scrapper(problem):
    parts = problem.split('/')
    if 'group' in parts:
        return 'Problem in private group'
    if 'problemset' in parts:
        idx = parts.index('problem')
        return parts[idx + 1] + '-' + parts[idx + 2]
    if 'contest' or 'gym' in parts:
        idx = parts.index('problem')
        return parts[idx - 1] + '-' + parts[idx + 1]
    

def get_problem_links(file):
    f = open(file, "r")
    problems = f.read().split('\n')
    return problems


def create_driver():
    chrome_options = webdriver.ChromeOptions()
    # chrome_options.add_argument("--headless")
    chrome_options.add_argument("--disable-dev-shm-usage")
    chrome_options.add_argument("--no-sandbox")
    driver = webdriver.Chrome(options=chrome_options)
    return driver


def find_element(driver, by, value, timeout=30):
    return WebDriverWait(driver, timeout).until(EC.visibility_of_element_located((by, value)))


def main():
    email = os.getenv('CODEFORCES_HANDLE')
    password = os.getenv('CODEFORCES_PASSWORD')
    sheet_name = os.getenv('SHEET_NAME')
    
    if not sheet_name or not email or not password:
        print('Missing environment variables')
        return

    problems = [scrapper(problem) for problem in get_problem_links('Problems_Links.txt')]
        
    driver = create_driver()
    time.sleep(2)
    driver.get("https://codeforces.com/enter") 
    time.sleep(3)
    driver.execute_script("window.stop();")
    time.sleep(2)
    find_element(driver, By.ID, 'handleOrEmail').send_keys(email)
    find_element(driver, By.ID, 'password').send_keys(password)
    time.sleep(2)
    find_element(driver, By.CLASS_NAME, 'submit').click()
    time.sleep(2)
    driver.get('https://codeforces.com/mashup/new')
    time.sleep(2)
    driver.execute_script("window.stop();")
    contest_name = driver.find_element(By.CSS_SELECTOR, '#contestName')
    contest_name.send_keys(sheet_name)
    duration = driver.find_element(By.CSS_SELECTOR, '#contestDuration')
    duration.send_keys('10080')
    
    for problem in problems:
        problem_id = driver.find_element(By.CSS_SELECTOR, '._MashupContestEditFrame_addProblem > label:nth-child(2) > input:nth-child(1)')
        problem_id.send_keys(problem)
        time.sleep(2)
        driver.find_element(By.CSS_SELECTOR, '._MashupContestEditFrame_addProblemLink > img:nth-child(1)').click()
        time.sleep(2)
        
    driver.find_element(By.CSS_SELECTOR, 'html body div#body div div#pageContent.content-with-sidebar div._MashupContestEditFrame_frame form._MashupContestEditFrame_saveMashup.table-form input.submit').click()
    time.sleep(2)
    driver.close()
    
    
if __name__ == "__main__":
    main()