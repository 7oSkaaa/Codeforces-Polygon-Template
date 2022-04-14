import os
import time
from dotenv import load_dotenv
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait

load_dotenv()

# Colors to use
red = '\033[38;5;196m'
green = '\033[38;5;40m'
blue = '\033[34m'


# To make the problem in the valid format for being added to codeforces
def scrapper(problem):
    if 'polygon' in problem:
        return problem
    parts = problem.split('/')
    if 'group' in parts or 'task' in parts or 'leetcode.com' in parts or not problem:
        return 'Invalid Problem'
    if 'problemset' in parts:
        idx = parts.index('problem')
        return parts[idx + 1] + '-' + parts[idx + 2]
    if 'contest' or 'gym' in parts:
        idx = parts.index('problem')
        return parts[idx - 1] + '-' + parts[idx + 1]
    

# Get links of the problem from the file
def get_problem_links(file):
    f = open(file, "r")
    problems = f.read().strip().split('\n')
    return problems


# Create chrome driver
def create_driver():
    chrome_options = webdriver.ChromeOptions()
    chrome_options.add_argument("--headless")
    chrome_options.add_argument("--disable-dev-shm-usage")
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-notifications")
    chrome_options.add_argument("--disable-popup-blocking")
    driver = webdriver.Chrome(options=chrome_options)
    return driver


# make timeout 30 seconds for command find element
def find_element(driver, by, value, timeout=30):
    return WebDriverWait(driver, timeout).until(EC.visibility_of_element_located((by, value)), f'{red}Timeout while trying to reach an element')


def main():
    
    # get environment variables we need
    email = os.getenv('CODEFORCES_HANDLE')
    password = os.getenv('CODEFORCES_PASSWORD')
    sheet_name = os.getenv('SHEET_NAME')
    sheet_duration = os.getenv('SHEET_DURATION')
    
    #check if there missing environment variables
    if not sheet_name or not email or not password:
        print(f'{red}\nMissing environment variables')
        return

    # get the problems in the valid format
    problems = [scrapper(problem) for problem in get_problem_links('Problems_Links.txt')]
        
    #check if there is invalid problems
    if 'Invalid Problem' in problems:
        print(f'{red}\nInvalid Problem in Problems...')
        return
    
    #check if there is problem to add or not
    if not problems:
        print(f'\n{red}Invalid in parsing problems or the Problems_Links.txt is empty\n')
        return
    
    # check if there is more than 26 problems
    if len(problems) > 26:
        print(f'{red}\nCannot create sheet on codeforces with more than 26 problems')
        return
    
    driver = create_driver()
    
    # sign in codeforces
    driver.get("https://codeforces.com/enter") 
    print(f'{blue}\nlogging in...\n')
    find_element(driver, By.ID, 'handleOrEmail').send_keys(email)
    find_element(driver, By.ID, 'password').send_keys(password)
    find_element(driver, By.CLASS_NAME, 'submit').click()
    time.sleep(3)
    
    # check if the driver can logging in successfuly
    if 'Login' in driver.title:
        print(f'{red}\nFailed to logginng in to codeforces')
        return
    else:
        print(f'{green}\nlogging in successfuly ✅\n')
    
    # go to new mushup page
    driver.get('https://codeforces.com/mashup/new')
    print(f'{blue}\nCreating the sheet...\n')
    time.sleep(3)
    find_element(driver, By.CSS_SELECTOR, '#contestName').send_keys(sheet_name)
    find_element(driver, By.CSS_SELECTOR, '#contestDuration').send_keys(sheet_duration)
    
    # add the problems to the gym
    for problem in problems:
        find_element(driver, By.CSS_SELECTOR, '._MashupContestEditFrame_addProblem > label:nth-child(2) > input:nth-child(1)').send_keys(problem)
        find_element(driver, By.CSS_SELECTOR, '._MashupContestEditFrame_addProblemLink > img:nth-child(1)').click()
        time.sleep(1)
        
    find_element(driver, By.CSS_SELECTOR, 'html body div#body div div#pageContent.content-with-sidebar div._MashupContestEditFrame_frame form._MashupContestEditFrame_saveMashup.table-form input.submit').click()
    print(f'{green}\nSheet has been added successfully ✅\n')
    time.sleep(3)
    driver.close()
    
    
if __name__ == "__main__":
    main()