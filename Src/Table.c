#include <userint.h>
#include "Table.h"
#include "LoadPanel.h"
#include "TablePanel.h"
#include "Protocol.h" 

Table_TypeDef Table_ATTR;


void Table(char table_title[][20], int column,int  columnWidth,int row) //初始化列名设置    
{			
		   
	                               
			InsertTableColumns(hTablePanel,TABLE_DISTABLE,1,column,VAL_CELL_STRING);                     //向表中插入多少列 
			InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1 , row, VAL_CELL_STRING);				      //插入row行 
			switch(TestPara.testMode)
			{
				case SWEEP_GATE_VOL: 
				case SWEEP_DRAIN_VOL:
				case NO_SWEEP_IT:
				case NO_SWEEP_RT:
					for(int j=1;j<=column;j++)
					{	
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //启用列首
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //设置列宽
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+2)%3]); //列标号
						SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (j, 1), table_title[(j+2)%3]);	          //分别设置标题
					}
					break;
				case SWEEP_IV:
					for(int j=1;j<=column;j++)
					{
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //启用列首
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //设置列宽
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+1)%2]); //列标号
						SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (j, 1),table_title[(j+2)%3]);	          //分别设置标题
					}
					break;
				case ID_T:
					for(int j=1;j<=column;j++)
					{
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //启用列首
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //设置列宽
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+3)%4]); //列标号
						SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (j, 1),table_title[(j+3)%4]);	          //分别设置标题
					}
					break;
				}
		
			
			
}

 //隔行添加背景色
int CVICALLBACK ColorCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{		 
	   switch(event){
		case EVENT_LEFT_CLICK_UP:
			int val;
			GetCtrlVal(hTablePanel,TABLE_ADDBGCOLOR,&val); //获得checkbox的值
			 int rowIndex;
             int numRows;
			 GetNumTableRows (hTablePanel, TABLE_DISTABLE, &numRows);
			   for (rowIndex=1; rowIndex <= numRows; rowIndex++)
		        {
		         if((val) &&((rowIndex % 2) ==1))
					 SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, 0xD0D0D0L);//灰色      
		         else
		             SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);//白色   
		        }
		
	 	   break;
	    } 

	return 0;
}




