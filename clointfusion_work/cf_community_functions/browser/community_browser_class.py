import logging 
import sys 
from selenium.common.exceptions import InvalidArgumentException, TimeoutException, WebDriverException, NoSuchWindowException, SessionNotCreatedException, ElementNotInteractableException, UnexpectedAlertPresentException, InvalidSelectorException
from webdriver_manager import driver


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




























class FirefoxBrowser:
    def __init__(self):
        import selenium.webdriver as webdriver
        from selenium.webdriver.firefox.options import Options
        from webdriver_manager.firefox import GeckoDriverManager
        self.options = Options()
        self.options.add_argument("--start-maximized")
        self.options.add_experimental_option('excludeSwitches', ['enable-logging'])
        try:
            with DisableLogger():
                self.browser_driver = webdriver.Firefox(GeckoDriverManager().install(), options=self.options)
        except Exception as e:
            print(f"Error while creating browser driver: {e}")

    def close_browser(self):
        self.browser_driver.close()
        self.browser_driver.quit()

    def __del__(self):
        self.close_browser()



















# def browser_select_dropdown_option_h(by_label:str='',by_xpath:str='',set_value:str='')->None:
#     '''
#     Args:
#         by_label:
#     Function:

#     Sets the Dropdown option either by label or by xpath with the given value.
#     '''
#     try:
#         if not by_label and not by_xpath:
#             elem = gui_get_dropdownlist_values_from_user('Select either a label or xpath of the dropdown element',dropdown_list=['by_label','by_xpath'],multi_select=False)
#             if elem == 'by_label':
#                 by_label = gui_get_any_input_from_user('Pass the label name to locate the dropdown element')
#             else:
#                 by_xpath = gui_get_any_input_from_user('Pass the xpath of the dropdown element')

#         if not set_value:
#             set_value = gui_get_any_input_from_user('The text to set in the dropdown ')

#         if set_value != '':
#             if by_label != '':
#                 browser_h.select(browser_h.ComboBox(label=by_label),value=set_value)

#             elif by_xpath != '':
#                 browser_h.select(browser_h.S(selector=by_xpath).web_element,value=set_value)

#             else:
#                 raise Exception("Either 'by_label' or 'by_xpath' should be passed.")
#         else:
#             raise Exception("Missing important parameter 'set_value'.")

#     except Exception as e:
#         print(f'Error in browser_select_dropdown_option_h = {e}')



















# def browser_attach_file_h(path_of_file:str='',to_xpath:str='')->None:
#     '''

#     Args : 

#     path_of_file : path of file to attach
#     to_xpath : xpath of element to attach file to

#     Returns : 
#         None 

#     Function : 

#     Uploads the selected file to the respective xpath location
#     '''
#     import os 
#     try:
#         if not path_of_file:
#             path_of_file = gui_get_any_input_from_user('Full path of file')
#         if not to_xpath:
#             to_xpath = gui_get_any_input_from_user('Enter the xpath of attachment button/location')

#         if os.path.exists(path_of_file):
#             elem_xpath = browser_h.S(to_xpath).web_element
#             browser_h.attach_file(file_path=path_of_file,to=elem_xpath)
#         else:
#             raise Exception('File can\'t be found.')
#     except Exception as e:
#         print(f'Error in browser_attach_file_h = {e}')





























# def browser_get_title_h()->str:
#     """
#     Returns the Browser Window Title (string)
#     """
#     try:
#         if helium_service_launched:
#             if browser_driver :
#                 return browser_driver.title

#             else:
#                 raise Exception("Browser isn't initialized. Call browser_launch_h() to initialize the browser")
#         else:
#             raise Exception('No Helium Service Launched.')

#     except Exception as ex:
#         print(f'Error in browser_get_title_h() = {ex}')
#         return False 
      































# def mouse_find_highlight_click(searchText:str="",delay:float=0.1,occurrence:int=1,left_right:str="left",single_double_triple:str="single",copyToClipBoard_Yes_No:str="no")->None:
    
    
#     """
#     Args:
#         searchText (str): The text to search for.
#         delay (float): The delay between each click.
#         occurrence (int): The number of times to try a click.
#         left_right (str): The mouse button to  click. (left click or right click)
#         single_double_triple (str): The number of times to click. (single/ double/triple)

#     Returns : 
#         None


#     Searches the given text on the screen, highlights and clicks it.
#     """  

#     import time
#     import pyautogui as pg  
#     import cv2
#     from skimage.metrics import structural_similarity
#     import imutils
#     import logging 



#     try:
#         if not searchText:
#             searchText = gui_get_any_input_from_user("search text to Highlight & Click")

#         time.sleep(0.2)

#         find_text_on_screen(searchText,delay=delay,occurance=occurrence,isSearchToBeCleared = True) #clear the search

#         img = pg.screenshot()
#         img.save(ss_path_b)
#         time.sleep(0.2)
#         imageA = cv2.imread(ss_path_b)
#         time.sleep(0.2)

#         find_text_on_screen(searchText,delay=delay,occurance=occurrence,isSearchToBeCleared = False) #dont clear the searched text

#         img = pg.screenshot()
#         img.save(ss_path_a)
#         time.sleep(0.2)
#         imageB = cv2.imread(ss_path_a)
#         time.sleep(0.2)

#         # convert both images to grayscale
#         grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
#         grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)

#         # compute the Structural Similarity Index (SSIM) between the two
#         (_, diff) = structural_similarity(grayA, grayB, full=True)
#         diff = (diff * 255).astype("uint8")

#         thresh = cv2.threshold(diff, 0, 255,
#             cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]
#         cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
#             cv2.CHAIN_APPROX_SIMPLE)
#         cnts = imutils.grab_contours(cnts)

#         # loop over the contours
#         for c in cnts:
#             (x, y, w, h) = cv2.boundingRect(c)
            
#             X = int(x + (w/2))
#             Y = int(y + (h/2))
            
#             mouse_click(x=X,y=Y,left_or_right=left_right,single_double_triple=single_double_triple,copyToClipBoard_Yes_No=copyToClipBoard_Yes_No)
#             time.sleep(0.5)
#             break

#     except Exception as ex:
#         print(f"Error in mouse_find_highlight_click={ex}")
#     finally:
#         logging.info("mouse_find_highlight_click")

































# def mouse_search_snip_return_coordinates_box(img:str="", conf:float=0.9, wait=180,region:tuple[float,float,float,float]=(0,0,pg.size()[0],pg.size()[1]))->tuple[float,float]:
#     """
#     Args : 
#     img : image path to the image to be searched
#     conf : confidence level of the search
#     wait : time to wait for the search to be completed
#     region : region of the screen to search in (x,y,w,h)

#     Returns :
#     (x,y) : coordinates of the box

#     Searches the given image on the screen and returns the 4 bounds co-ordinates (x,y,w,h)
#     """
#     import time 
#     import pyautogui as pg 
#     import logging
#     status = False
#     try:
#         if not img:
#             img = gui_get_any_file_from_user("snip image file, to get BOX coordinates","png")

#         time.sleep(1)
        
#         pos = pg.locateOnScreen(img,confidence=conf,region=region) 
#         i = 0
#         while pos == None and i < int(wait):
#             pos = ()
#             pos = pg.locateOnScreen(img, confidence=conf,region=region)   
#             time.sleep(1)
#             i = i + 1
#         time.sleep(1)
        

#     except Exception as ex:
#         print(f"Error in mouse_search_snip_return_coordinates_box = {ex}")
#     else:
#         status = True 
        

#     finally:
#         logging.info(f"mouse_search_snip_return_coordinates_box = {img}")
#         return pos if status else status 
        


























# def mouse_search_snips_return_coordinates_x_y(img_lst:list=[], conf:float=0.9, wait:float=180, region=(0,0,pg.size()[0],pg.size()[1])):
#     """

#     Args:
#     img_list : list of image names to search for
#     conf : confidence parameter (closer to 0 anything would match else closer to 1 only exact image matches, 0.8 is reccomended )
#     wait : the total wait (delay) time for the images to be found
#     region = (x,y,w,h) the region to search in

#     Function: 

#     Searches the given set of images on the screen and returns its center of X Y co-ordinates of FIRST OCCURRENCE




#     """ 
#     import os 
#     import time
#     import pyautogui as pg
#     from pathlib import Path
#     import logging 

#     status = False
#     position = None 
#     try:
#         if not img_lst:
#             img_lst_folder_path = gui_get_folder_path_from_user("folder having snip image files, to get X,Y coordinates of any one")

#             for img_file in img_lst:
#                 img_file = os.path.join(img_lst_folder_path,img_file)

#                 img_file = Path(str(img_file))

#                 img_lst.append(img_file)

#         time.sleep(1)

#         if len(img_lst) > 0:
#             #Logic = Locate Image Immediately
#             pos = ()
#             for img in img_lst:
#                 pos = pg.locateOnScreen(img,confidence=conf,region=region) 
#                 if pos != None:
#                     break

#             #Logic = Locate Image with Delay
#             i = 0
#             while pos == None and i < int(wait):
#                 pos = ()

#                 for img in img_lst:
#                     pos = pg.locateOnScreen(img,confidence=conf,region=region) 

#                 time.sleep(1)
#                 i = i + 1

#             time.sleep(1)

#             if pos:
#                 x,y = pos.left + int(pos.width / 2), pos.top + int(pos.height / 2)
#                 position = ()
#                 position = (x,y)
#             else:
#                 position = None    
         
        
#     except Exception as ex:
#         print(f"Error in mouse_search_snips_return_coordinates_x_y={ex}")
#     else:
#         status = True 
#     finally:
#         logging.info("is_text_found_on_screen=")
#         if status and position:
#             return position
#         else:
#             return None

        

































# def mouse_get_color_by_position(x:int="",y:int="", delay:float=3)->str:
#     """Gets the color by X Y co-ordinates of the screen. Default it takes current mouse position
#     Args:
#         x (int): x-coordinate on screen.
#         Eg: 369 or 435, Defaults: ''.
#         y (int): y-coordinate on screen.
#         Eg: 369 or 435, Defaults: ''.
#         delay (int): Time to wait before getting current position
#     Returns:
#         bool: If the function is failed return False.
#         string: RGB code of the color
#     """
#     import time 
#     import pyautogui as pg 


#     status = False
#     rgb_value = None
#     try:
#         time.sleep(delay)
#         if not x or not y:
#             x, y = pg.position()
#         im = pg.screenshot()
#         time.sleep(0.5)
#         x,y = int(x), int(y)
#         rgb_value = im.getpixel((x, y))
#     except Exception as ex:
#         print(f"Error in mouse_get_color_by_position = {ex}")
#     else:
#         status = True
#     finally:
#          return rgb_value if status else  False 
        
            























# def browser_mouse_click_s(element=None,i:str="c")->None:   
#     """
#     Args: 
#        element : selenium element 
#        i : "c" clicks on the given element , "e" hits enter on the given element
#     Returns : 
#         None

#     Function : 

#     Clicks on given web element using XPath
#     """
   

#     status = True
#     try:                                              
#         if not element:
#             element = gui_get_any_input_from_user('browser element for Mouse Click')
            
#         if i == "c":
       
#             element.click()                                                

#         elif i == "e":
#             element.send_keys(Keys.ENTER)                                   
         
#     except Exception as ex:
#         status = False
#         print(f"Error in browser_mouse_click_s = {ex}")
#     finally:
#         logging.info(f"WebWrite={element} {i}")
        
