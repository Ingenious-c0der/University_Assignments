def mouse_get_color_by_position(x:int="",y:int="", delay:float=3)->str:
    """Gets the color by X Y co-ordinates of the screen. Default it takes current mouse position
    Args:
        x (int): x-coordinate on screen.
        Eg: 369 or 435, Defaults: ''.
        y (int): y-coordinate on screen.
        Eg: 369 or 435, Defaults: ''.
        delay (int): Time to wait before getting current position
    Returns:
        bool: If the function is failed return False.
        string: RGB code of the color
    """
    import time 
    import pyautogui as pg 


    status = False
    rgb_value = None
    try:
        time.sleep(delay)
        if not x or not y:
            x, y = pg.position()
        im = pg.screenshot()
        time.sleep(0.5)
        x,y = int(x), int(y)
        rgb_value = im.getpixel((x, y))
    except Exception as ex:
        print(f"Error in mouse_get_color_by_position = {ex}")
    else:
        status = True
    finally:
         return rgb_value if status else  False
        
def mouse_search_snips_return_coordinates_x_y(img_lst:list=[], conf:float=0.9, wait:float=180, region=(0,0,pg.size()[0],pg.size()[1]))->tuple[float,float]:
    """

    Args:
    img_list : list of image names to search for
    conf : confidence parameter (closer to 0 anything would match else closer to 1 only exact image matches, 0.8 is reccomended )
    wait : the total wait (delay) time for the images to be found
    region = (x,y,w,h) the region to search in

    Function: 

    Searches the given set of images on the screen and returns its center of X Y co-ordinates of FIRST OCCURRENCE




    """ 
    import os 
    import time
    import pyautogui as pg
    from pathlib import Path
    import logging 

    status = False
    position = None
    found_image = None
    try:
        if not img_lst:
            raise Exception("img_lst is empty")


        for img_file in img_lst:
                img_file = os.path.join(img_lst_folder_path,img_file)

                img_file = Path(str(img_file))

                img_lst.append(img_file)

        time.sleep(1)

        if len(img_lst) > 0:
            #Logic = Locate Image Immediately
            pos = ()
            for img in img_lst:
                pos = pg.locateOnScreen(img,confidence=conf,region=region) 
                if pos != None:
                    found_image = img
                    break

            #Logic = Locate Image with Delay
            i = 0
            while pos == None and i < int(wait):
                pos = ()

                for img in img_lst:
                    pos = pg.locateOnScreen(img,confidence=conf,region=region)
                    found_image = img

                time.sleep(1)
                i = i + 1

            time.sleep(1)

            if pos:
                x,y = pos.left + int(pos.width / 2), pos.top + int(pos.height / 2)
                position = ()
                position = (x,y)
            else:
                found_image = None
                position = None    
         
    except Exception as ex:
        print(f"Error in mouse_search_snips_return_coordinates_x_y={ex}")
    else:
        status = True 
    finally:
        
            logging.info(f"mouse_search_snips_return_coordinates_x_y = {found_image}")
            
            return position
       
    
def mouse_search_snip_return_coordinates_box(img:str="", conf:float=0.9, wait=180,region:tuple[float,float,float,float]=(0,0,pg.size()[0],pg.size()[1]))->tuple[float,float]:
    """
    Args : 
    img : image path to the image to be searched
    conf : confidence level of the search
    wait : time to wait for the search to be completed
    region : region of the screen to search in (x,y,w,h)

    Returns :
    (x,y) : coordinates of the box

    Searches the given image on the screen and returns the 4 bounds co-ordinates (x,y,w,h)
    """
    import time 
    import pyautogui as pg 
    import logging
    status = False
    try:
        if not img:
            raise Exception("img is empty")

        time.sleep(1)
        
        pos = pg.locateOnScreen(img,confidence=conf,region=region) 
        i = 0
        while pos == None and i < int(wait):
            pos = ()
            pos = pg.locateOnScreen(img, confidence=conf,region=region)   
            time.sleep(1)
            i = i + 1
        time.sleep(1)
        

    except Exception as ex:
        print(f"Error in mouse_search_snip_return_coordinates_box = {ex}")
    else:
        status = True 
        

    finally:
        logging.info(f"mouse_search_snip_return_coordinates_box = {img}")
        return pos if status else status 
   


def mouse_find_highlight_click(searchText:str="",delay:float=0.1,occurrence:int=1,left_right:str="left",single_double_triple:str="single",copyToClipBoard_Yes_No:str="no")->bool:
    
    
    """
    Args:
        searchText (str): The text to search for.
        delay (float): The delay between each click.
        occurrence (int): The number of times to try a click.
        left_right (str): The mouse button to  click. (left click or right click)
        single_double_triple (str): The number of times to click. (single/ double/triple)
    Returns : 
        Bool : True if successful else False
    Searches the given text on the screen, highlights and clicks it.
    """  

    import time
    import pyautogui as pg  
    import cv2
    from skimage.metrics import structural_similarity
    import imutils
    import logging 

    status = False

    try:
        if not searchText:
            raise Exception("searchText is empty")

        time.sleep(0.2)

        find_text_on_screen(searchText,delay=delay,occurance=occurrence,isSearchToBeCleared = True) #clear the search

        img = pg.screenshot()
        img.save(ss_path_b)
        time.sleep(0.2)
        imageA = cv2.imread(ss_path_b)
        time.sleep(0.2)

        find_text_on_screen(searchText,delay=delay,occurance=occurrence,isSearchToBeCleared = False) #dont clear the searched text

        img = pg.screenshot()
        img.save(ss_path_a)
        time.sleep(0.2)
        imageB = cv2.imread(ss_path_a)
        time.sleep(0.2)

        # convert both images to grayscale
        grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
        grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)

        # compute the Structural Similarity Index (SSIM) between the two
        (_, diff) = structural_similarity(grayA, grayB, full=True)
        diff = (diff * 255).astype("uint8")

        thresh = cv2.threshold(diff, 0, 255,
            cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]
        cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)

        # loop over the contours
        for c in cnts:
            (x, y, w, h) = cv2.boundingRect(c)
            
            X = int(x + (w/2))
            Y = int(y + (h/2))
            
            mouse_click(x=X,y=Y,left_or_right=left_right,single_double_triple=single_double_triple,copyToClipBoard_Yes_No=copyToClipBoard_Yes_No)
            time.sleep(0.5)
            break

    except Exception as ex:
        print(f"Error in mouse_find_highlight_click={ex}")
    else:
        status= True
    finally:
        logging.info("mouse_find_highlight_click")
        return status
    


def excel_drag_drop_pivot_table(excel_path="",sheet_name='Sheet1', header=0,rows=[],cols=[])->bool:
    """
    Interactive pivot table function, which accepts excel file, X & Y column.
    Args:
        excel_path: Excel file path
        sheet_name: Sheet name
        header: Header row number
        rows: List of rows to be used for X axis
        cols: List of columns to be used for Y axis
    Returns:
        bool: True if pivot table is created, False otherwise
    """
    import os 
    status = False
    try:
        if not excel_path:
            raise Exception("excel_path is empty")
            
        if not rows:
            raise Exception("rows is empty")

        if not cols:
            raise Exception("cols is empty")

        excel_path = Path(excel_path)

        strFileName = excel_path.stem
        output_file = os.path.join(output_folder_path,strFileName + ".html")
        output_file = Path(output_file)
        
        df = pd.read_excel(excel_path,sheet_name=sheet_name,header=header, engine='openpyxl')
        pivot_ui(df, outfile_path=output_file,rows=rows, cols=cols)
        
        HTML(str(output_file))
        print("Please find the output at {}".format(output_file))
    
    except Exception as ex:
        print("Error in excel_drag_drop_pivot_table="+str(ex))
    else:
        status = True
    
    finally:
        logging.info("excel_drag_drop_pivot_table()=" + str(name) + " " + str(message))
        return status

def excel_draw_charts(excel_path="",sheet_name='Sheet1', header=0, x_col="", y_col="", color="", chart_type='bar', title='ClointFusion', show_chart=False)->bool:

    """
    Interactive data visualization function, which accepts excel file, X & Y column. 
    Chart types accepted are bar , scatter , pie , sun , histogram , box  , strip. 
    You can pass color column as well, having a boolean value.
    Image gets saved as .PNG in the same path as excel file.
    Usage: excel_charts(<excel path>,x_col='Name',y_col='Age', chart_type='bar',show_chart=True)

    """
    status= False
    try:
        if not excel_path:
           raise Exception("excel_path is empty")
            
        if not x_col:
            raise Exception("x_col is empty")

        if not y_col:
            raise Exception("y_col is empty") 

        if x_col and y_col:
            if color:
                df = pd.read_excel(excel_path,sheet_name=sheet_name,header=header,usecols={x_col,y_col,color}, engine='openpyxl')
            else:
                df = pd.read_excel(excel_path,sheet_name=sheet_name,header=header,usecols={x_col,y_col}, engine='openpyxl')

            fig = go.Figure()

            if chart_type == 'bar':

                fig.add_trace(go.Bar(x=df[x_col].values.tolist()))
                fig.add_trace(go.Bar(y=df[y_col].values.tolist()))

                if color:
                    fig = px.bar(df, x=x_col, y=y_col, barmode="group",color=color)
                else:
                    fig = px.bar(df, x=x_col, y=y_col, barmode="group")
                    
            elif chart_type == 'scatter':

                fig.add_trace(go.Scatter(x=df[x_col].values.tolist()))
                fig.add_trace(go.Scatter(y=df[x_col].values.tolist()))

            elif chart_type =='pie':

                if color:
                    fig = px.pie(df, names=x_col, values=y_col, title=title,color=color)#,hover_data=df.columns)
                else:
                    fig = px.pie(df, names=x_col, values=y_col, title=title)#,hover_data=df.columns)

            elif chart_type =='sun':

                if color:
                    fig = px.sunburst(df, path=[x_col], values=y_col,hover_data=df.columns,color=color)
                else:
                    fig = px.sunburst(df, path=[x_col], values=y_col,hover_data=df.columns)

            elif chart_type == 'histogram':

                if color:
                    fig = px.histogram(df, x=x_col, y=y_col, marginal="rug",color=color, hover_data=df.columns)
                else:
                    fig = px.histogram(df, x=x_col, y=y_col, marginal="rug",hover_data=df.columns)

            elif chart_type == 'box':

                if color:
                    fig = px.box(df, x=x_col, y=y_col, notched=True,color=color)
                else:
                    fig = px.box(df, x=x_col, y=y_col, notched=True)

            elif chart_type == 'strip':

                if color:
                    fig = px.strip(df, x=x_col, y=y_col, orientation="h",color=color)
                else:
                    fig = px.strip(df, x=x_col, y=y_col, orientation="h")

            fig.update_layout(title = title)
            
            if show_chart:
                fig.show()
            
            strFileName = _extract_filename_from_filepath(excel_path)
            strFileName = os.path.join(output_folder_path,strFileName + ".PNG")
            strFileName = Path(strFileName)
            
            scope = PlotlyScope()
            with open(strFileName, "wb") as f:
                f.write(scope.transform(fig, format="png"))
            print("Chart saved at " + strFileName)
        else:
            print("Please supply all the required values")

    except Exception as ex:
        print("Error in excel_draw_charts=" + str(ex))
    else:
        status = True
    finally:
    
        logging.info("excel_draw_charts")
        return status 

def excel_clean_data(excel_path="",sheet_name='Sheet1',header=0,column_to_be_cleaned="",cleaning_pipe_line="Default")->bool:
    """
    fillna(s) Replace not assigned values with empty spaces.
    lowercase(s) Lowercase all text.
    remove_digits() Remove all blocks of digits.
    remove_punctuation() Remove all string.punctuation (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~).
    remove_diacritics() Remove all accents from strings.
    remove_stopwords() Remove all stop words.
    remove_whitespace() Remove all white space between words.
    Returns:
        True if successful, False otherwise.
    """
    try:
        if not excel_path:
            raise Exception("excel_path is empty")
            
        if not column_to_be_cleaned:
            raise Exception("column_to_be_cleaned is empty")

        if column_to_be_cleaned:
            df = pd.read_excel(excel_path,sheet_name=sheet_name,header=header, engine='openpyxl')

            new_column_name = "Clean_" + column_to_be_cleaned

            if 'Default' in cleaning_pipe_line:
                df[new_column_name] = df[column_to_be_cleaned].pipe(hero.clean)
            else:
                custom_pipeline = [preprocessing.fillna, preprocessing.lowercase]
                df[new_column_name] = df[column_to_be_cleaned].pipe(hero.clean,custom_pipeline)    

            with pd.ExcelWriter(path=excel_path) as writer:
                df.to_excel(writer,index=False)

            print("Data Cleaned. Please see the output in {}".format(new_column_name))
    except Exception as ex:
        print("Error in excel_clean_data="+str(ex))
    else:
        status = True
    finally:
        logging.info("excel_clean_data")
        return status

def excel_charts_numerical_pair_plot(excel_path="", sheet_name="", header=0, usecols="",show_chart=False)->bool:
    """
    Args:
        excel_path:path to excel file
        sheet_name:sheet name
        header:header row
        usecols:columns to be used
        show_chart:bool
    Funtion for statistical data visualization.
    Returns:
        bool : True if successful, False otherwise.
    """
    status = False
    try:
        if not excel_path:
            raise Exception("excel_path is empty")

        if not usecols:
            raise Exception("usecols is empty")

        df = pd.read_excel(excel_path, sheet_name=sheet_name, header=header, usecols=usecols, engine='openpyxl')
        
        # df = sb.load_dataset('iris')
        g = sb.PairGrid(df)
        g.map(plt.scatter)
        g.map_diag(plt.hist)
        g.map_offdiag(plt.scatter)
        
        mng = plt.get_current_fig_manager()
        mng.full_screen_toggle()
        plt.tight_layout()
        
        strFileName = _extract_filename_from_filepath(excel_path)
        strFileName = os.path.join(output_folder_path,strFileName + ".PNG")
        strFileName = Path(strFileName)

        plt.savefig(strFileName)
        if show_chart:
            plt.show()
    
        print("Chart saved at " + strFileName)

    except Exception as ex:
        print("Error in excel_charts_numerical_pair_plot="+str(ex))
    else:
        status = True
    finally:
        logging.info("excel_charts_numerical_pair_plot")
        return status

def excel_charts_correlation_heatmap(excel_path="", sheet_name="", header=0, usecols="",show_chart=False)->bool:
    """
    Function for co-relation between columns of the given excel
    Args:
        excel_path:path to excel file
        sheet_name:sheet name
        header:header row
        usecols:columns to be used
        show_chart:bool
    Returns:
        bool : True if successful, False otherwise.
    """
    status = False
    try:
        if not excel_path:
            raise Exception("excel_path is empty")

        if not usecols:
            raise Exception("usecols is empty")

        df = pd.read_excel(excel_path, sheet_name=sheet_name, header=header, usecols=usecols, engine='openpyxl')
        sb.heatmap(df.corr(), annot = True, cmap = 'viridis')

        strFileName = _extract_filename_from_filepath(excel_path)

        strFileName = os.path.join(output_folder_path,strFileName + ".PNG")
        strFileName = Path(strFileName)
        
        plt.savefig(strFileName)
        print("Chart saved at " + str(strFileName))

        mng = plt.get_current_fig_manager()
        mng.full_screen_toggle()
        plt.tight_layout()
        
        plt.savefig(strFileName)
        if show_chart:
            plt.show()
    except Exception as ex:
        print("Error in excel_charts_correlation_heatmap="+str(ex))
    else:
        status = True
    finally:
        
        logging.info("excel_charts_correlation_heatmap")
        return status


def excel_set_formula(excel_path="",sheet_name='Sheet1',target_cell="",formula="",cell_format='General')->bool:
    """
    Function to set formula to a particular excel cell
    Args:
        excel_path:path to excel file
        sheet_name:sheet name
        target_cell:cell to set formula
        formula:formula to be set
        cell_format:cell format
    Returns:
        bool : True if successful, False otherwise.
    """
    status = False
    try:
        if not excel_path:
            raise Exception("excel_path is empty")

        if not target_cell:
            raise Exception("target_cell is empty")

        if not formula:
            raise Exception("formula is empty")

        wb = op.load_workbook(excel_path)
        ws = wb[sheet_name]

        ws[target_cell] = formula

        ws[target_cell].number_format = cell_format
        
        wb.save(excel_path)
    except Exception as ex:
        print("Error in excel_set_formula="+str(ex))
    else:
        status  = True
    finally :
        logging.info("excel_set_formula")
        return status

def excel_apply_template_format_save_to_new(excel_rawdata_file_path='',excel_newfile_path='',rawexcel_sheet_name='Sheet1', usecols='',template_file_path='',template_sheet_name="Sheet1")->bool:

    '''
        Converts given excel to Template Excel
        This function uses pandas and just write the required columns to new excel.
        if you don't know columns, just pass the excel file which have the columns you want it automatically makes 
        own list and remove other columns.
    '''
    status = False 
    try:
        if type(usecols) == str:
            usecols = [usecols]
        if template_file_path:
            usecols = excel_get_all_header_columns(excel_path=template_file_path,sheet_name=template_sheet_name)
        elif not template_file_path :
            df = pd.read_excel(excel_rawdata_file_path, sheet_name=rawexcel_sheet_name,usecols=usecols)
        if excel_newfile_path:
            df.to_excel(excel_newfile_path,index=False)
        else :
            df.to_excel(excel_rawdata_file_path,index=False)
        if enable_semi_automatic_mode == False:
            show(df)

    
    except Exception as e:
        exception_msg = f"Error in converting given excel to template excel : {str(e)}"
    else:
        status = True
    finally:
        logging.info("excel_apply_template_format_save_to_new")
        return status
def sentiment_analysis(inputText:str="")->bool:
    """
    Function to analyse sentiments based on input text. 
    Returns 3 values: POSITIVE / NEUTRAL / NEGATIVE
    Ex: sentiment_analysis('Hare Krishna, you are awesome')
    """
    status = False
    try:
        if not inputText:
            raise Exception("inputText is empty")

        analyzer = SentimentIntensityAnalyzer()
        vs = analyzer.polarity_scores(inputText)
        
        if vs['compound'] >= 0.05:
            print('Sentiment is POSITIVE '+show_emoji('thumbsup'))

        elif vs['compound'] > -0.05 and vs['compound'] < 0.05:
            print('Sentiment is NEUTRAL '+show_emoji('neutral_face'))

        elif vs['compound'] <= -0.05:
            print('Sentiment is NEGATIVE '+show_emoji('thumbsdown'))

    except Exception as ex:
        print("Error in sentiment_analysis="+str(ex))
    else:
        status = True
    finally:
        logging.info("sentiment_analysis")
        return status

def camera_capture_image(user_name:str="")->bool:
    """
    Function to capture image from camera and save it to current directory.
    Args:
        user_name:user name
    Returns True if successful, False otherwise."""
    status = False 
    try:

        user_consent = gui_get_consent_from_user("turn ON camera & take photo ?")

        if user_consent == 'Yes':
            SECONDS = 5
            TIMER = int(SECONDS) 
            window_name = "ClointFusion"
            cap = cv2.VideoCapture(0) 

            if not cap.isOpened():
                print("Error in opening camera")

            cv2.namedWindow(window_name, cv2.WND_PROP_FULLSCREEN)
            cv2.setWindowProperty(window_name, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
            font = cv2.FONT_HERSHEY_SIMPLEX 

            if not user_name:
                raise Exception("user_name is empty")

            while True: 

                ret, img = cap.read() 
                cv2.imshow(window_name, img) 
                prev = time.time() 

                text = "Taking selfie in 5 second(s)".format(str(TIMER))
                textsize = cv2.getTextSize(text, font, 1, 2)[0]
                print(str(textsize))

                textX = int((img.shape[1] - textsize[0]) / 2)
                textY = int((img.shape[0] + textsize[1]) / 2)

                while TIMER >= 0: 
                    ret, img = cap.read() 

                    cv2.putText(img, "Saving image in {} second(s)".format(str(TIMER)),  
                                (textX, textY ), font, 
                                1, (255, 0, 255), 
                                2) 
                    cv2.imshow(window_name, img) 
                    cv2.waitKey(125) 

                    cur = time.time() 

                    if cur-prev >= 1: 
                        prev = cur 
                        TIMER = TIMER-1

                ret, img = cap.read() 
                cv2.imshow(window_name, img) 
                cv2.waitKey(1000) 
                file_path = os.path.join(output_folder_path,user_name + ".PNG")
                file_path = Path(file_path)
                cv2.imwrite(file_path, img) 
                print("Image saved at {}".format(file_path))
                cap.release() 
                cv2.destroyAllWindows()
                break

        else:
            print("Operation cancelled by user")
    except Exception as ex:
        print("Error in camera_capture_image="+str(ex))
    else:
        status = True
    finally:
        logging.info("camera_capture_image")
        return status
    

def word_cloud_from_pdf(path_to_pdf:str="")->bool:
    """
    Function to create word cloud from a given PDF
    Args:
        path_to_pdf:path to pdf file
    Returns True if successful, False otherwise.
    """
    status = False
    try:

        text = pdf_text_extract(path_to_pdf=path_to_pdf)
        
        wc = WordCloud(max_words=2000, width=800, height=600, max_font_size=40, random_state=None, background_color='black',relative_scaling=0)
        wc.generate(text)
        file_path = os.path.join(output_folder_path,"PDF_WordCloud.png")
        file_path = Path(file_path)
        wc.to_file(file_path)
        print("PDF WordCloud saved at {}".format(file_path))
    except Exception as ex:
        print("Error in word_cloud_from_pdf="+str(ex))
    else:
        status = True
    finally:
        logging.info("word_cloud_from_pdf")
        return status


def word_cloud_from_excel(excel_path="",sheet_name="",header=0,columnNames="")->bool:
    """
    Function to create word cloud from a given website
    Args:
        excel_path:path to excel file
        sheet_name:sheet name
        header:header row number
        columnNames:column names
    Returns True if successful, False otherwise.
    """
    import os 
    status = False
    try:
        if not excel_path:
            raise Exception("excel_path is empty")
            
        if not columnNames:
            raise Exception("columnNames is empty")  

        df = pd.read_excel(excel_path,sheet_name=sheet_name,header=header, engine='openpyxl')

        text = ""

        if columnNames:
            for col in columnNames:
                text = ''.join(str(list(df[col])))
                text = text.replace("\n"," ")
        
        wc = WordCloud(max_words=2000, width=800, height=600, max_font_size=40, random_state=None, relative_scaling=0)
        wc.generate(text)
        
        file_path = os.path.join(output_folder_path,"Excel_WordCloud.png")
        file_path = Path(file_path)
        
        wc.to_file(file_path)

        print("Excel WordCloud saved at {}".format(file_path))

    except Exception as ex:
        print("Error in word_cloud_from_excel="+str(ex))
    else:
        status = True
    finally:
        logging.info("word_cloud_from_excel")
        return status

def pdf_text_extract(path_to_pdf="")->str:
    """
    Extract data from PDF(s). Works best on machine-generated PDF, than scanned.
    Args:
        path_to_pdf:path to pdf file
    Returns text extracted from PDF(s)

    """
    status = False
    try:
        if not path_to_pdf:
            raise Exception("path_to_pdf is empty")

        pdf_text = ""

        with pdfplumber.open(path_to_pdf) as pdf:
            total_pages = int(len(pdf.pages))
            print("Total PDF page(s)="+str(total_pages))
            for i in range(total_pages):
                page = pdf.pages[i]
                pdf_text = pdf_text + page.extract_text()
                
    except Exception as ex:
        print("Error in pdf_text_extract="+str(ex))
    else:
        status = True
    finally:
        logging.info("pdf_text_extract")
        return pdf_text if status else False

def word_cloud_from_url(url="")->bool:
    """
    Function to create word cloud from a given website
    Args:
        url:url of the website
    Returns True if successful, False otherwise.
    
    """
    status = False
    try:
        text = browser_get_html_text(url=url)
        
        wc = WordCloud(max_words=2000, width=800, height=600,background_color='white',max_font_size=40, random_state=None, relative_scaling=0)
        wc.generate(text)
        file_path = os.path.join(output_folder_path,"URL_WordCloud.png")
        file_path = Path(file_path)
        wc.to_file(file_path)
        print("URL WordCloud saved at {}".format(file_path))

    except Exception as ex:
        print(f"Error in word_cloud_from_url={ex}")
    else:
        status = True
    finally:
        logging.info("word_cloud_from_url")
        return status
        
