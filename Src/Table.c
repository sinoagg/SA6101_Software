#include <userint.h>
#include "Table.h"
#include "LoadPanel.h"
#include "TablePanel.h"
#include "Protocol.h" 

Table_TypeDef Table_ATTR;
char AB[11][20] ={"A","B","C"};

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
				case ID_T:
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
				}
		
			
			
}
//添加列名
int CVICALLBACK AddTitleCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	/*switch (event)											  
	{
		case EVENT_LEFT_CLICK_UP:
			Table_init(Table_title_IT,column, column_width );
			SetCtrlAttribute (hTablePanel, TABLE_ADDROW, ATTR_DIMMED,0);       
			SetCtrlAttribute (hTablePanel, TABLE_ADDTITLE,  ATTR_DIMMED,1); 				
			break;
	}*/
	return 0;
}

//添加行数
int CVICALLBACK AddRowCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{   	switch (event)
	{			   
			case EVENT_LEFT_CLICK_UP:
				/*int row;
   	            InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1, 1, VAL_CELL_NUMERIC);				          //插入1行 
				GetNumTableRows (hTablePanel, TABLE_DISTABLE, &row); 										  //得到当前行数
				for(int i=1;i<=column;i++){
					//添加表格内容
					 SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (i,row ), i*100.0);//第i列     
					//内容居中显示效果   
					 SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (i,row ), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED); 
				}
					int MaxRow; //超出tanle高度后显示总能显示最后一行数据 
					GetNumTableRows(hTablePanel,TABLE_DISTABLE,&MaxRow);
					SetCtrlAttribute(hTablePanel,TABLE_DISTABLE,ATTR_FIRST_VISIBLE_ROW,MaxRow);*/
							
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
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1);
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);	
		    SetCtrlAttribute (hTablePanel, TABLE_ADDROW, ATTR_DIMMED,1);       
		    SetCtrlAttribute (hTablePanel, TABLE_ADDTITLE,  ATTR_DIMMED,0);
	 	 
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




