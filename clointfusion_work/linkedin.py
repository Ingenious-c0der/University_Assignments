from selenium import webdriver
import time 
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.options import Options
from loguru import logger
import keyboard
from instabot import Bot 
import glob
from dotenv import load_dotenv
import os
load_dotenv(os.path.join(os.getcwd(),"secret.env"))


class LinkedIn:
    def __init__(self,email_id:str,password:str):
        self.email_id = email_id
        self.password = password
        logger.debug("Initializing LinkedIn ...")
        chrome_options = Options()
        chrome_options.add_argument("--headless")
        chrome_options.add_argument("--no-sandbox")
        chrome_options.add_argument("--log-level=3")
        self.driver = webdriver.Chrome(ChromeDriverManager().install(),options=chrome_options)
        logger.debug("LinkedIn initialized")

    def login(self):
        logger.debug("Logging in to LinkedIn ...")
        self.driver.get("https://www.linkedin.com/login?fromSignIn=true&trk=guest_homepage-basic_nav-header-signin")
        time.sleep(2)
        self.driver.find_element_by_id("username").send_keys(self.email_id)
        self.driver.find_element_by_id("password").send_keys(self.password)

        self.driver.find_element_by_xpath("//button[@type='submit']").click()
        time.sleep(3)
        try:
            self.driver.find_element_by_xpath("//button[@type='button']").click()
        except:
            pass
        logger.debug("Logged in to LinkedIn")

    def post(self,caption:str,image_link:str):
        logger.debug("Creating the LinkedIn post ...")
        element = self.driver.find_element_by_xpath("//button[@class = 'artdeco-button artdeco-button--muted artdeco-button--4 artdeco-button--tertiary ember-view share-box-feed-entry__trigger']")
        self.driver.execute_script("arguments[0].click();", element)
        
        time.sleep(2)
        self.driver.find_element_by_xpath("//div[@class='ql-editor ql-blank']").send_keys(caption+"\n"+image_link )
        time.sleep(1)
        self.driver.find_element_by_xpath("//button[@class='share-actions__primary-action artdeco-button artdeco-button--2 artdeco-button--primary ember-view']").click()

        logger.debug("LinkedIn post created")


    def close(self):
        self.driver.close()

