import logging 
import sys
import helium 
from selenium.common.exceptions import InvalidArgumentException, TimeoutException, WebDriverException, NoSuchWindowException, SessionNotCreatedException, ElementNotInteractableException, UnexpectedAlertPresentException, InvalidSelectorException


class DisableLogger():
    def __enter__(self):
       logging.disable(logging.CRITICAL)
    def __exit__(self, exit_type, exit_value, exit_traceback):
       logging.disable(logging.NOTSET)

class ChromeBrowser:
    """Class to create and use a webdriver independent of other number of active drivers.
        Args : 
        incognito (optional): Boolean, True if incognito mode is to be used. Default is False.

        dummy_browser (optional): Boolean, True if dummy browser is to be used. Default is True.If it is false Default profile is opened.

        profile (optional): String, profile name to be used. Default is "Default".


    """

    _instance = None
            
    def __init__(self):
                self.browser_driver = None
                 
    def open(self, dummy_browser:bool=True, profile:str="Default", incognito:bool=False )->bool:
        """Open the browser.
        Args:
            dummy_browser (bool, optional): True to open dummy browser.
            profile: profile to be used Eg.Profile 3 .Defaults: "Default".
            incognito (bool, optional): True to open incognito mode.

        Returns:
            bool: Whether the function is successful or failed.
            """
        
        import selenium.webdriver as webdriver
        from webdriver_manager.chrome import ChromeDriverManager
        from selenium.webdriver.chrome.service import Service
        import os
        from selenium.webdriver.chrome.options import Options
        import helium
                
        self.options = Options()
        
        self.options.add_argument("--start-maximized")
        self.options.add_experimental_option('excludeSwitches', ['enable-logging', 'enable-automation'])
        status = False
        try:
          with DisableLogger():
            if not dummy_browser:
                self.options.add_argument("user-data-dir=C:\\Users\\{}\\AppData\\Local\\Google\\Chrome\\User Data".format(os.getlogin()))
                self.options.add_argument(f"profile-directory={profile}")
            if incognito:
                self.options.add_argument("--incognito")
            self.service  = Service(ChromeDriverManager().install())
            self.browser_driver = webdriver.Chrome(service = self.service, options=self.options)
            self.browser_driver.get("https://www.google.com")
            helium.set_driver(self.browser_driver)
            helium.Config.implicit_wait_secs = 60
        except Exception as e:
            print(f"Error while creating browser driver: {e}")
        else:
            status = True
        finally:
            return status
        

    def navigate(self,url:str='')->bool:
        """Navigate through the url after the session is started.
        Args:
            url (str, optional): Url which you want to visit. 
            Defaults: "".
        Returns:
            bool: Whether the function is successful or failed.
        """

        status = False 
        if not url:
            self.browser_driver.get("https://www.google.com")

        try:
            if not url :
                self.browser_driver.get("https://www.google.com")
            else:
                self.browser_driver.get(url)
        except:
            print("Error while navigating to url")
        else:
            status = True
        
        finally:
            return status

    def write(self,text:str='',user_visible_text_element:str="")->bool:
        """Write a string in browser, if user_visible_text_element is given it writes on the given element.
        Args:
        text (str, optional): String which has be written. 
        Defaults: "".
        user_visible_text_element (str, optional): The element which is visible(Like : Sign in). 
        Defaults: "".
        Returns:
        bool: Whether the function is successful or failed.
        """
    

        status = False
        import helium 
        helium.set_driver(self.browser_driver)
        try:
            
            
            if text and user_visible_text_element:
                helium.write(text, into=user_visible_text_element)
               
            if text and not user_visible_text_element:
                helium.write(text)
     
        except AttributeError:
            print("Invalid Input. Please check the given input.")
            sys.exit()
        except TimeoutException:
            print("Element not found. Please check the given input or change browser_set_waiting_time().")
            sys.exit()
        except Exception as e :
            print(e)
        else:
            status = True
        finally:
            return status

    def mouse_click(self,User_Visible_Text_Element:str="", element:str="", double_click:bool=False, right_click:bool=False)->bool:
        """Click on the given element.
        Args:
            User_Visible_Text_Element (str, optional): The element which is visible(Like : Sign in). 
            Defaults: "".
            element (str, optional): Use locate_element to get element and use to click. 
            Defaults: "".
            double_click (bool, optional): True to perform a Double click. 
            Defaults: False.
            right_click (bool, optional): True to perform a Right click. 
            Defaults: False.
        Returns:
            bool: Whether the function is successful or failed.
        """
        import helium 
        status = False
        helium.set_driver(self.browser_driver)
        
        try:
            if not double_click and not right_click:
                if User_Visible_Text_Element and not element:
                    helium.click(User_Visible_Text_Element)
                if not User_Visible_Text_Element and element:
                        helium.click(element)
                
            if double_click and not right_click:
                if User_Visible_Text_Element and not element:
                        helium.doubleclick(User_Visible_Text_Element)
                if not User_Visible_Text_Element and element:
                        helium.doubleclick(element)
               
            if right_click and not double_click:
                if User_Visible_Text_Element and not element:
                        helium.rightclick(User_Visible_Text_Element)
                if not User_Visible_Text_Element and element:
                        helium.rightclick(element)
                


        except AttributeError:
            print("Invalid Input. Please check the given input.")

            sys.exit()
        except Exception as e:
            print(e)
        else:
            status = True

        finally:
            return status  
  
    def wait_until(self,text:str="", element:str="t")->bool:
        """Wait until a specific element is found.
        Args:
            text (str, optional): To wait until the string appears on the screen. 
            Eg: Export Successfull Completed. Defaults: ""
            element (str, optional): Type of Element Whether its a Text(t) or Button(b). 
            Defaults: "t - Text".
        Returns:
            bool: Whether the function is successful or failed.
        """
        import helium
        helium.set_driver(self.browser_driver)
        status = False
        try:
            
            if element.lower() == "t":
                helium.wait_until(helium.Text(text).exists, 10) # text
               
            
            elif element.lower() == "b":
                helium.wait_until(helium.Button(text).exists, 10) # button
            
        except TimeoutException:
            print("Element not found. Please check the given input or change browser_set_waiting_time().")
           
            sys.exit()
        except Exception as e:
            print(e)
        
        else:
            status = True

        finally:
            return status
  
    def refresh_page(self)->bool:
        """Refresh the current active browser page.
        Returns:
            bool: Whether the function is successful or failed.
        """
        status = False
        try:
            self.browser_driver.refresh()
          
        except Exception as e:
            print(e)
        else:
            status = True
        finally:
            return status

    def hit_enter(self)->bool:
        """Hits enter KEY in Browser
        Returns:
            bool: Whether the function is successful or failed.
        """
        status = False
        import helium
        helium.set_driver(self.browser_driver)
        try:
            helium.press(helium.ENTER)
           
        except Exception as e:
            print(e)
        else:
            status = True
        finally:
            return status

    def key_press(self,key_1:str="", key_2:str="")->bool: 
        """Type text using Browser Helium Functions and press hot keys.
        Args:
            key_1 (str): Keys you want to simulate or string you want to press 
            Eg: "tab" or "Murali". Defaults: ""
            key_2 (str, optional): Key you want to simulate with combination to key_1. 
            Eg: "shift" or "escape". Defaults: ""
        
        Returns:
            bool: Whether the function is successful or failed.
        """
        status = False

        from selenium.webdriver.common.keys import  Keys

        browser_keys = {"enter":Keys.ENTER, "shift":Keys.SHIFT, "tab":Keys.TAB, "alt":Keys.ALT, "escape":Keys.ESCAPE, "esc":Keys.ESCAPE, "ctrl":Keys.CONTROL, "control":Keys.CONTROL}
        try:
  
            hot_keys = list(browser_keys.keys())

            if set([key_1.lower(),key_2.lower()]).issubset( hot_keys ):
                key_1 = browser_keys[key_1.lower()]
                key_2 = browser_keys[key_2.lower()]

                self.browser_driver.switch_to.active_element.send_keys(key_1,key_2)
                
            elif key_1.lower() in hot_keys and key_2.lower() not in hot_keys:
                key_1 = browser_keys[key_1.lower()]
                self.browser_driver.switch_to.active_element.send_keys(key_1)
            
            elif key_2.lower() in hot_keys and key_1.lower() not in hot_keys:
                key_2 = browser_keys[key_2.lower()]
                self.browser_driver.switch_to.active_element.send_keys(key_2)
            else:
                print("Invalid keys combination")
                return False
            
        except TimeoutException:
            print("Element not found. Please check the given input or change browser_set_waiting_time().")
        
        except AttributeError:
            print("Invalid Input. Please check the given input.")
           
            sys.exit()
        except Exception as e:
            print(e)

        else:
            status = True

        finally:
            return status
  
    def mouse_hover(self,User_Visible_Text_Element:str="")->bool:
        """Performs a Mouse Hover over the Given User Visible Text Element
        Args:
            User_Visible_Text_Element (str, optional): The element which is visible(Like : Sign in). 
            Defaults: "".
        Returns:
            bool: Whether the function is successful or failed.
        """
        status = False
        import helium
        try:
            helium.hover(helium.Text(User_Visible_Text_Element))
        
        except Exception as e:
            print(e)
        else:
            status = True
           
        finally:
            return status
 
    def set_waiting_time(self,time:float=10)->bool:
        """
        Set the waiting time for the self.browser_driver. If element is not found in the given time, it will raise an exception.
        Args:
            time ([int]): The time in seconds to wait for the element to be found.
        Returns:
            bool: Whether the function is successful or failed.
        """
        import helium
        status = False
        try:
            helium.set_driver(self.browser_driver)
            helium.Config.implicit_wait_secs = int(time)
        except Exception as e:
            print(e)
        else:
            status = True
        finally:
            return status

        
    def __str__(self):
        return f"Chrome Browser with options: {self.options.experimental_options} Profile : {self.profile}"
    
    def close(self):
        self.browser_driver.close()
        self.browser_driver.quit()

    def locate_element(self,selector="",get_text:bool=False,multiple_elements:bool = False):
        """Find the element by Xpath, id or css selection.
        Args:
            selector (str, optional): Give Xpath or CSS selector. Defaults to "".
            get_text (bool, optional): Give the text of the element. Defaults to False.
            multiple_elements (bool, optional): True if you want to get all the similar elements with matching selector as list. Defaults to False.
        Returns:
            element         : If only one element
            list of elements: If multiple_elements is True

        """
        import helium
        helium.set_driver(self.browser_driver)
        
        try:
            if not multiple_elements:
                if get_text:
                    return helium.S(selector).web_element.text
                return helium.S(selector)
            if multiple_elements:
                if get_text:
                    return helium.find_all(helium.S(selector).web_element.text)
                return helium.find_all(helium.S(selector))
        except Exception as ex:
            print(f"Error in browser_locate_element_h = {ex}")




        
    def get_title(self):
        """
        Returns:
         The Browser Window Title
         False if the function fails to get the title

        """
        import helium
        title = False
        helium.set_driver(self.browser_driver)
        try:
                title = helium.Window.title
        except Exception as ex:
            print(f'Error in get_title = {ex}')
        finally:
            return title


    def attach_file(self,path_of_file:str='',to_xpath='')->bool:
        '''
        Upload the selected file to the respected xpath location
        Args:
            path_of_file (str, optional): The path of the file to be uploaded. Defaults to "".
            to_xpath (str, optional): The xpath of the file upload location. Defaults to "".
        Returns:
            bool: Whether the function is successful or failed.
        '''
        import helium
        import os 
        status = False
        helium.set_driver(self.browser_driver)
        try:
           
            if os.path.exists(path_of_file):
                elem_xpath = helium.S(to_xpath).web_element
                helium.attach_file(file_path=path_of_file,to=elem_xpath)
            else:
                raise Exception('File can\'t be found.')
        except Exception as e:
            print('Error in browser_attach_file_h = ',str(e))
        else:
            status = True
        finally:
            return status

    def select_dropdown_option(self,by_label='',by_xpath='',set_value='')->bool:
        '''
        Sets the Dropdown option either by label or by xpath with the given value.
        Args:
            by_label (str, optional): The label of the dropdown. Defaults to "".
            by_xpath (str, optional): The xpath of the dropdown. Defaults to "".
            set_value (str, optional): The value to be set in the dropdown. Defaults to "".

        Returns:
            bool: Whether the function is successful or failed.
        '''
        import helium
        helium.set_driver(self.browser_driver)
        status = False 
        try:

            if set_value != '':
                if by_label != '':
                    helium.select(helium.ComboBox(label=by_label),value=set_value)

                elif by_xpath != '':
                    helium.select(helium.S(selector=by_xpath).web_element,value=set_value)

                else:
                    raise Exception("Either 'by_label' or 'by_xpath' should be passed.")
            else:
                raise Exception("Missing important parameter 'set_value'.")

        except Exception as e:
            print('Error in browser_select_dropdown_option_h = ',str(e))
        else:
            status = True
        finally:
            return status

    def get_dropdown_options(self,label='')->list:
        '''
        Returns the available options in the given labelled dropdown.
        Args:
            label (str, optional): The label of the dropdown. Defaults to "".
        
        '''
        import helium
        status = False
        Data = False 
        helium.set_driver(self.browser_driver)
        try:
            Data = helium.ComboBox(label=label).options
            
        except Exception as e:
            print('Error in browser_get_dropdown_options_h = ',str(e))
        else:
            status = True
        finally:
            if status:
                return Data

   
    def get_page_source_html(self)->str:
        """
        Gets the complete html page source of the given page as string.
        Returns:
            str: The complete html page source of the given page.
        """
        status = False

        data = False
        try:
            #Get whole HTML Source in the page as List
            data =  self.browser_driver.page_source     
        except Exception as ex:
            print("Error in browser_get_page_source_html = "+str(ex))
        else:
            status = True
        finally:
            logging.info("browser_get_page_source_html")
            if status:
                return data 

    def get_page_source_text(self)->list:
        """
        Gets complete text of the given page as list.
        Returns:
            list: The complete text of the given page.
            False if the function failed.
        """    
        try:                                     
            #Get whole text in the page as List
            text_items = []
            data = self.browser_driver.find_elements_by_tag_name('html')
            for item in data:
                text_items.append(item.text)
            
        except Exception as ex:
            print("Error in browser_get_page_source_text = "+str(ex))
        else:
            status = True

        finally:
            
            logging.info("browser_get_page_source_text")
            return text_items if status else False

    def navigate_action(self,nav:str)->bool:
        """
        Navigates to given url or goes forward, backward or refresh according to the specified argument.
        
        """
        status = False
        try:
            if len(nav) >5 :
                #Navigate to URL
                self.browser_driver.get(nav)                 
                
            elif nav.lower() == "b" :             
                #Navigate Back
                self.browser_driver.back()
                
            elif nav.lower() == "f" :       
                #Navigate Forward       
                self.browser_driver.forward()
                return
            elif nav.lower() == "r" :    
                #Refresh Page         
                self.browser_driver.refresh()
                return
        except Exception as ex:
            print("Error in browser_navigate_s = "+str(ex))
            
        else:
            status = True
        finally:
            logging.info("browser_navigate_s="+str(nav))
            return status
        
    def locate_elements(self,element ="",type_="xpath"):
        """
        Args:
            xpath of the element to be found
        type_:
            xpath
        Locates the XPATH elements on screen and return the elements.
        """
        elements = False
        status = False
        try:
            #change it to xpath
            if type_.lower() == "xpath":
                elements = self.browser_driver.find_elements_by_xpath(element)               
                
            elif type_.lower() == "href":
                #find by link text href
                elements = self.browser_driver.find_element_by_link_text(element)            
               
            elif type_.lower() == "css":          
                #find by css selector                                
                elements = self.browser_driver.find_element_by_css_selector(element)
               
        except Exception as ex:
            print("Error in browser_locate_elements_s = "+str(ex))
        else:
            status = True
        finally:
            logging.info("browser_locate_elements_s="+str(element))
            return elements if status else False

    def search_image(self,img,confidence):
         
        """
        Internal Function
        """
        from python_imagesearch.imagesearch import region_grabber
        from python_imagesearch.imagesearch import imagesearcharea
        import pyautogui as pg 
        try:
            w,h = pg.size()  
            im = region_grabber((0, 0, w, h))
            pos = imagesearcharea(img, 0, 0, w, h, confidence, im)
            if pos[0] > 0 and pos[1] > 0 :
                return pos
        except Exception as ex:
            print("Errror in _search_image="+str(ex))
        finally:
            logging.info("_search_image")
        
    def search_multiple_images(self,img_lst=[], confidence=0.9)->tuple:
        """
        Returns the postion of all the images passed as list
        Args:
            img_lst (list, optional): List of images to be searched. Defaults to [].
            confidence (float, optional): Confidence level of the search. Defaults to 0.9.
        Returns:
            list: List of tuples containing the position of the image.
        """
        from joblib import Parallel, delayed
        status = False
        results = []
        try:
            if not img_lst:
                raise Exception("No image list passed.")

            if len(img_lst) > 0 :
                results = Parallel(n_jobs=10)(delayed(self.search_image)(img,confidence) for img in img_lst)
                
        except Exception as ex:
            print("Errror in search_multiple_images_in_parallel="+str(ex))
        else:
            status = True

        finally:
            logging.info("search_multiple_images_in_parallel")
            return results if status else False

    def scroll(self,direction:str="down",weight = 3)->bool:
        """Scrolls the browser window.
        Args:
            direction (str, optional): The direction to scroll. Defaults: "down".u,d,l,r
            weight  : The weight of the scroll. Defaults: 3. 3 corresponds to 300 pixs
        Returns:
            bool: Whether the function is successful or failed.
        """
        status = False
        import helium
        helium.set_driver(self.browser_driver)
        scroll_pixs  = weight * 100
        try:
            if direction.lower() == "down":
                helium.scroll_down(scroll_pixs)
            elif direction.lower() == "up":
                helium.scroll_up(scroll_pixs)
            elif direction.lower()=="left":
                helium.scroll_left(scroll_pixs)
            elif direction.lower()=="right":
                helium.scroll_right(scroll_pixs)

            status = True
        except Exception as e:
            print(e)
           
        finally:
            return status
