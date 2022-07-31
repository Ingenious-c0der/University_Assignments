from selenium import webdriver
import time 
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.options import Options
from loguru import logger
import keyboard
from instabot import Bot 
import glob
import os
from dotenv import load_dotenv
load_dotenv(os.path.join(os.getcwd(),"secret.env"))



driver = webdriver.Chrome(ChromeDriverManager().install())
driver.get("https://www.gmail.com")
time.sleep(5)
driver.find_element_by_id("identifierId").send_keys(os.getenv("GMAIL_EMAIL_ID"))
element = driver.find_element_by_xpath("//div[@class='VfPpkd-RLmnJb']")
driver.execute_script("arguments[0].click();", element)
time.sleep(2)
driver.find_element_by_name("password").send_keys(os.getenv("GMAIL_PASSWORD"))
driver.find_element_by_xpath("//div[@class='VfPpkd-RLmnJb']")
driver.execute_script("arguments[0].click();", element)



