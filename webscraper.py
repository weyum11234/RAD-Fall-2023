from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By

driver = webdriver.Chrome()
driver.get('https://tunebat.com/Analyzer')

driver.implicitly_wait(0.5)

search_box = driver.find_element(By.TAG_NAME, 'input')
search_btn = driver.find_element(By.TAG_NAME, 'button')

search_box.send_keys(input('Enter name of song: '))
search_btn.click()

driver.implicitly_wait(0.5)

bpm_result = driver.find_elements(By.TAG_NAME, 'p')[2]
bpm_value = int(bpm_result.text)

print('BPM is', bpm_value)

driver.quit()