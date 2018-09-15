# it is quite slow while loading pages , maybe I'll improve it later.
from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import Select
import sys

FILENAME = sys.argv[1]
FILETYPE = FILENAME.split('.')[-1] # TODO: can't handel python files.

# load page
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

driver = webdriver.Safari()
# TODO: waiting for the page to load wastes time, may try parallel.
driver.get('http://pythontutor.com/visualize.html#mode=edit')
try:
    element = WebDriverWait(driver, 30).until(
        EC.presence_of_element_located((By.ID, "pythonVersionSelector"))
    )
    # a tricky way to protect the input codes' indentations.
    select = Select(element)
    select.select_by_value('js')
finally:
    # input code
    dest = driver.find_element_by_css_selector('textarea.ace_text-input')
    code = open(FILENAME, 'r')
    for line in code.readlines():
        dest.send_keys(line.strip() + '\n') # also for indentation
    # select FILETYPE, then press execute button.
    select.select_by_value(FILETYPE)
    driver.find_element_by_id("executeBtn").click()
