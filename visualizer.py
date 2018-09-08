from selenium import webdriver
from selenium.common.exceptions import TimeoutException
from selenium.webdriver.support.ui import Select
import sys

FILENAME = sys.argv[1]
FILETYPE = FILENAME.split('.')[-1] # TODO: can't handel python files.

# load page
driver = webdriver.Chrome()
# TODO: waiting for the page load wastes time, maybe try parallel.
driver.set_page_load_timeout(20)
try:
    driver.get('http://pythontutor.com/visualize.html#mode=edit')
except TimeoutException as e:
    driver.execute_script("window.stop();")

# a tricky way to protect the input codes' indentations.
select = Select(driver.find_element_by_id('pythonVersionSelector'))
select.select_by_value('js')

# input code
dest = driver.find_element_by_css_selector('textarea.ace_text-input')
code = open(FILENAME, 'r')
for line in code.readlines():
    dest.send_keys(line.strip() + '\n') # also for indentation

# select FILETYPE, then press execute button.
select.select_by_value(FILETYPE)
driver.find_element_by_id("executeBtn").click()
