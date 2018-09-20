#include <userint.h>
#include "Table.h"
#include "LoadPanel.h"
#include "TablePanel.h"
#include "Protocol.h" 

Table_TypeDef Table_ATTR;


void Table(char table_title[][20], int column,int  columnWidth,int row) //��ʼ����������    
{			
		   
	                               
			InsertTableColumns(hTablePanel,TABLE_DISTABLE,1,column,VAL_CELL_STRING);                     //����в�������� 
			InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1 , row, VAL_CELL_STRING);				      //����row�� 
			switch(TestPara.testMode)
			{
				case SWEEP_GATE_VOL: 
				case SWEEP_DRAIN_VOL:
				case NO_SWEEP_IT:
				case NO_SWEEP_RT:
					for(int j=1;j<=column;j++)
					{	
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //��������
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //�����п�
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+2)%3]); //�б��
						SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (j, 1), table_title[(j+2)%3]);	          //�ֱ����ñ���
					}
					break;
				case SWEEP_IV:
					for(int j=1;j<=column;j++)
					{
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //��������
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //�����п�
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+1)%2]); //�б��
						SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (j, 1),table_title[(j+2)%3]);	          //�ֱ����ñ���
					}
					break;
				case ID_T:
					for(int j=1;j<=column;j++)
					{
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //��������
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //�����п�
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+3)%4]); //�б��
						SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (j, 1),table_title[(j+3)%4]);	          //�ֱ����ñ���
					}
					break;
				}
		
			
			
}

 //������ӱ���ɫ
int CVICALLBACK ColorCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{		 
	   switch(event){
		case EVENT_LEFT_CLICK_UP:
			int val;
			GetCtrlVal(hTablePanel,TABLE_ADDBGCOLOR,&val); //���checkbox��ֵ
			 int rowIndex;
             int numRows;
			 GetNumTableRows (hTablePanel, TABLE_DISTABLE, &numRows);
			   for (rowIndex=1; rowIndex <= numRows; rowIndex++)
		        {
		         if((val) &&((rowIndex % 2) ==1))
					 SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, 0xD0D0D0L);//��ɫ      
		         else
		             SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);//��ɫ   
		        }
		
	 	   break;
	    } 

	return 0;
}




