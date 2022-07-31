

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
            excel_path, sheet_name, header = gui_get_excel_sheet_header_from_user('for Pivot Table Generation')
            
        if not rows:
            col_lst = excel_get_all_header_columns(excel_path, sheet_name, header)
            rows = gui_get_dropdownlist_values_from_user('row fields',col_lst,multi_select=True)

        if not cols:
            col_lst = excel_get_all_header_columns(excel_path, sheet_name, header)
            cols = gui_get_dropdownlist_values_from_user('column fields',col_lst,multi_select=True)

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
            excel_path, sheet_name, header = gui_get_excel_sheet_header_from_user('for data visualization')
            
        if not x_col:
            col_lst = excel_get_all_header_columns(excel_path, sheet_name, header)
            x_col = gui_get_dropdownlist_values_from_user('X Axis Column',col_lst,multi_select=False)[0]  

        if not y_col:
            col_lst = excel_get_all_header_columns(excel_path, sheet_name, header)
            y_col = gui_get_dropdownlist_values_from_user('Y Axis Column',col_lst,multi_select=False)[0]  

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
            excel_path, sheet_name, header = gui_get_excel_sheet_header_from_user('to clean the data')
            
        if not column_to_be_cleaned:
            col_lst = excel_get_all_header_columns(excel_path, sheet_name, header)  
            column_to_be_cleaned = gui_get_dropdownlist_values_from_user('column list to Clean (removes digits/puntuation/stop words etc)',col_lst,multi_select=False)   
            column_to_be_cleaned = column_to_be_cleaned[0]

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
            excel_path, sheet_name, header = gui_get_excel_sheet_header_from_user('for pair plot charts')

        if not usecols:
            col_lst = excel_get_all_header_columns(excel_path, sheet_name, header)
            usecols = gui_get_dropdownlist_values_from_user('column list (minimum 2), to use for Pair Plot',col_lst)   

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
            excel_path, sheet_name, header = gui_get_excel_sheet_header_from_user('for correlation heatmap charts')

        if not usecols:
            col_lst = excel_get_all_header_columns(excel_path, sheet_name, header)
            usecols = gui_get_dropdownlist_values_from_user('column list (minimum 2) to use for Co-relation heatmap',col_lst)

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
        return status
        logging.info("excel_charts_correlation_heatmap")


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
