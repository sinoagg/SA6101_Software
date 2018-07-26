#include <userint.h>
#include "Table.h"
#include "LoadPanel.h"
/*
Table_TypeDef Table_ATTR*/;

char ABC[11][20] ={"A","B","C","D","E","F","G","H","I","J","K"};

char Table_title_IV[11][20] ={"Current(A)","Voltage(V)","Current(A)","Voltage(V)"};
char Table_title_VI[11][20] ={"Current(A)","Voltage(V)","Current(A)","Voltage(V)"}; 
char Table_title_IT[11][20] ={"Current(A)","Time(S)","Current(A)","Time(S)"};
<<<<<<< HEAD
 int column=4;//列数
=======
 int column=4;        //列数
>>>>>>> c470c37cb1316d04d8132fad4521adc588b849fd
 int column_width=285;//列宽


 //初始化列名设置
   void Table_init(char table_title_IV[][20], int column, column_width)
{						    
			
			InsertTableColumns(tablePanel,TABLE_DISTABLE,1,column,VAL_CELL_STRING);              //向表中插入多少列 
			InsertTableRows (tablePanel,TABLE_DISTABLE ,-1 , 1, VAL_CELL_STRING);				      		  //插入1行 
			for(int i=1;i<column+1;i++)
			{
			SetTableColumnAttribute(tablePanel,TABLE_DISTABLE,i,ATTR_USE_LABEL_TEXT,1);                     //启用列首
			SetTableColumnAttribute(tablePanel,TABLE_DISTABLE,i,ATTR_COLUMN_WIDTH,column_width); 			  //设置列宽
			SetTableColumnAttribute(tablePanel, TABLE_DISTABLE, i, ATTR_LABEL_TEXT, ABC[i-1]);              //列标号
		    SetTableCellVal (tablePanel, TABLE_DISTABLE, MakePoint (i, 1), table_title_IV[i-1]);	          //分别设置标题 

			
			}
			
}
<<<<<<< HEAD

=======
//添加列名
int CVICALLBACK AddTitleCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)											  
	{
		case EVENT_LEFT_CLICK_UP:
			Table_init(Table_title_IT,column, column_width );
			
			SetCtrlAttribute (tablePanel, TABLE_ADDROW, ATTR_DIMMED,0);       
			SetCtrlAttribute (tablePanel, TABLE_ADDTITLE,  ATTR_DIMMED,1); 				
			break;
	}
	return 0;
}
>>>>>>> c470c37cb1316d04d8132fad4521adc588b849fd

//添加行数
int CVICALLBACK AddRowCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{   	switch (event)
	{			   
				case EVENT_LEFT_CLICK_UP:
			
			
						    int row;
   	                  		InsertTableRows (tablePanel,TABLE_DISTABLE ,-1, 1, VAL_CELL_NUMERIC);				          //插入1行 
							GetNumTableRows (tablePanel, TABLE_DISTABLE, &row); 										  //得到当前行数
						    SetTableCellVal (tablePanel, TABLE_DISTABLE, MakePoint (1,row ), 100.0);
							SetTableCellVal (tablePanel, TABLE_DISTABLE, MakePoint (2,row ), 200.0); 
							SetTableCellVal (tablePanel, TABLE_DISTABLE, MakePoint (3,row ), 300.0); 
							SetTableCellVal (tablePanel, TABLE_DISTABLE, MakePoint (4,row ), 400.0);
<<<<<<< HEAD
=======
							int MaxRow;//最后一行行数
							GetNumTableRows(tablePanel,TABLE_DISTABLE,&MaxRow);
							SetCtrlAttribute(tablePanel,TABLE_DISTABLE,ATTR_FIRST_VISIBLE_ROW,MaxRow);
>>>>>>> c470c37cb1316d04d8132fad4521adc588b849fd
				break;
	}
	return 0;
}
//删除行列
int CVICALLBACK DeleteCalback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
				case EVENT_LEFT_CLICK_UP:
			DeleteTableRows (tablePanel, TABLE_DISTABLE, 1, -1);
	 		DeleteTableColumns (tablePanel, TABLE_DISTABLE, 1, -1);	
		    SetCtrlAttribute (tablePanel, TABLE_ADDROW, ATTR_DIMMED,1);       
		    SetCtrlAttribute (tablePanel, TABLE_ADDTITLE,  ATTR_DIMMED,0);
	 		//DeleteTableColumns (tablePanel, ADDPANEL_TABLE, 1, -1);
			//SetCtrlAttribute (tablePanel, ADDPANEL_ADDROW, ATTR_DIMMED,1);       
			//SetCtrlAttribute (tablePanel, TABLE_COMMANDBUTTON,  ATTR_DIMMED,0);  
			break;	
	}
	return 0;
}
 //隔行添加背景色
int CVICALLBACK ColorCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{		 
	
	
	  switch(event){
		case EVENT_LEFT_CLICK_UP:
			int CheckValue;
			GetCtrlVal(tablePanel,TABLE_ADDBGCOLOR,&CheckValue); //获得checkbox的值

			
					 
			 int rowIndex;
             int numRows;
			 GetNumTableRows (tablePanel, TABLE_DISTABLE, &numRows);
			   for (rowIndex=1; rowIndex <= numRows; rowIndex++)
		        {
		         if((CheckValue) &&((rowIndex % 2) ==1))
					 SetTableCellRangeAttribute (tablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, 0xD0D0D0L);//灰色      
		        
		        else
		               SetTableCellRangeAttribute (tablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);//白色   
		        }
		
	 	   break;
	    } 

	return 0;
}



<<<<<<< HEAD
//添加列名
int CVICALLBACK AddTitleCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)											  
	{
		case EVENT_LEFT_CLICK_UP:
			Table_init(Table_title_IT,column, column_width );
			
			SetCtrlAttribute (tablePanel, TABLE_ADDROW, ATTR_DIMMED,0);       
			SetCtrlAttribute (tablePanel, TABLE_ADDTITLE,  ATTR_DIMMED,1); 				
			break;
	}
	return 0;
}
=======

>>>>>>> c470c37cb1316d04d8132fad4521adc588b849fd
