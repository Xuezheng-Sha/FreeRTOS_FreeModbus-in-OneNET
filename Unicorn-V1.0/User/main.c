<<<<<<< HEAD:Unicorn-V1.0/User/main.c
#include "includes.h"
/*****************º¯ÊýÉùÃ÷*************/
static void vTaskFLASH(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
/*****************±äÁ¿ÉùÃ÷**************/
static TaskHandle_t xHandleTaskFLASH = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
/**
  * @brief  Ö÷Ñ­»·
  * @param  None
  * @retval None
  */
int main(void)
{         
          LCD_Init();
          KEY_Init();
          //LED_Init();
         //__set_PRIMASK(1); 
        //³õÊ¼»¯ RTUÄ£Ê½ ´Ó»úµØÖ·Îª1 USART1 9600 ÎÞÐ£Ñé
          eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
        //Æô¶¯FreeModbus 
          eMBEnable();
        // ´´½¨ÈÎÎñ
        AppTaskCreate();
                
        /* Æô¶¯µ÷¶È£¬¿ªÊ¼Ö´ÐÐÈÎÎñ */
        vTaskStartScheduler();
        /* 
        Èç¹ûÏµÍ³Õý³£Æô¶¯ÊÇ²»»áÔËÐÐµ½ÕâÀïµÄ£¬ÔËÐÐµ½ÕâÀï¼«ÓÐ¿ÉÄÜÊÇÓÃÓÚ¶¨Ê±Æ÷ÈÎÎñ»òÕß¿ÕÏÐÈÎÎñµÄ
        heap¿Õ¼ä²»×ãÔì³É´´½¨Ê§°Ü£¬´ËÒª¼Ó´óFreeRTOSConfig.hÎÄ¼þÖÐ¶¨ÒåµÄheap´óÐ¡£º
        #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
        */
                while(1);
}
/*
*********************************************************************************************************
*	º¯ Êý Ãû: vTaskFLASH
*	¹¦ÄÜËµÃ÷: ½Ó¿ÚÏûÏ¢´¦Àí£¬ÕâÀïÓÃ×÷FLASH
*	ÐÎ    ²Î: pvParameters ÊÇÔÚ´´½¨¸ÃÈÎÎñÊ±´«µÝµÄÐÎ²Î
*	·µ »Ø Öµ: ÎÞ
*   ÓÅ ÏÈ ¼¶: 1  (ÊýÖµÔ½Ð¡ÓÅÏÈ¼¶Ô½µÍ£¬Õâ¸ö¸úuCOSÏà·´)
*********************************************************************************************************
*/
//ÒªÐ´Èëµ½STM32 FLASHµÄ×Ö·û´®Êý×é
#define FLASH_SAVE_ADDR  0X08020000   
#define SIZE sizeof(FreeSize)	 	//Êý×é³¤¶È
u8 FreeSize[]={"STM32 ModbusTEST"};  
u8 datatemp[SIZE];   	
//ÉèÖÃFLASH ±£´æµØÖ·(±ØÐëÎªÅ¼Êý£¬ÇÒÆäÖµÒª´óÓÚ±¾´úÂëËùÕ¼ÓÃFLASHµÄ´óÐ¡+0X08000000)
static void vTaskFLASH(void *pvParameters)
{
   
    while(1)
    {
       //STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
      //STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)FreeSize,SIZE);
      vTaskDelay(100);
    }
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: vTaskLED
*	¹¦ÄÜËµÃ÷: LEDÉÁË¸	
*	ÐÎ    ²Î: pvParameters ÊÇÔÚ´´½¨¸ÃÈÎÎñÊ±´«µÝµÄÐÎ²Î
*	·µ »Ø Öµ: ÎÞ
*   ÓÅ ÏÈ ¼¶: 2  
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
    /* LEDÉÁË¸ */
    while(1)
    {
         LED0_ON();
       	
         vTaskDelay(100);
         LED0_OFF();
    }
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: vTaskMsgPro
*	¹¦ÄÜËµÃ÷: ÐÅÏ¢´¦Àí£¬ÕâÀïÊÇÓÃ×÷LEDÉÁË¸	
*	ÐÎ    ²Î: pvParameters ÊÇÔÚ´´½¨¸ÃÈÎÎñÊ±´«µÝµÄÐÎ²Î
*	·µ »Ø Öµ: ÎÞ
*   ÓÅ ÏÈ ¼¶: 3  
*********************************************************************************************************
*/
static void vTaskMsgPro(void *pvParameters)
{
    while(1)
    {
        
        eMBPoll(); 
        vTaskDelay(300);
    }
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: vTaskStart
*	¹¦ÄÜËµÃ÷: Æô¶¯ÈÎÎñ£¬Ò²¾ÍÊÇ×î¸ßÓÅÏÈ¼¶ÈÎÎñ£¬ÕâÀïÓÃ×÷LEDÉÁË¸
*	ÐÎ    ²Î: pvParameters ÊÇÔÚ´´½¨¸ÃÈÎÎñÊ±´«µÝµÄÐÎ²Î
*	·µ »Ø Öµ: ÎÞ
*   ÓÅ ÏÈ ¼¶: 4  
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
    while(1)
    {
        KEY_red();
        LED_Poll();
        vTaskDelay(400);
    }
}

/*
*********************************************************************************************************
*	º¯ Êý Ãû: AppTaskCreate
*	¹¦ÄÜËµÃ÷: ´´½¨Ó¦ÓÃÈÎÎñ
*	ÐÎ    ²Î£ºÎÞ
*	·µ »Ø Öµ: ÎÞ
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
    xTaskCreate( vTaskFLASH,   	/* ÈÎÎñº¯Êý  */
                 "vTaskFLASH",     	/* ÈÎÎñÃû    */
                 512,               	/* ÈÎÎñÕ»´óÐ¡£¬µ¥Î»word£¬Ò²¾ÍÊÇ4×Ö½Ú */
                 NULL,              	/* ÈÎÎñ²ÎÊý  */
                 1,                 	/* ÈÎÎñÓÅÏÈ¼¶*/
                 &xHandleTaskFLASH );  /* ÈÎÎñ¾ä±ú  */
	
	
	xTaskCreate( vTaskLED,    		/* ÈÎÎñº¯Êý  */
                 "vTaskLED",  		/* ÈÎÎñÃû    */
                 512,         		/* ÈÎÎñÕ»´óÐ¡£¬µ¥Î»word£¬Ò²¾ÍÊÇ4×Ö½Ú */
                 NULL,        		/* ÈÎÎñ²ÎÊý  */
                 2,           		/* ÈÎÎñÓÅÏÈ¼¶*/
                 &xHandleTaskLED ); /* ÈÎÎñ¾ä±ú  */
	
	xTaskCreate( vTaskMsgPro,     		/* ÈÎÎñº¯Êý  */
                 "vTaskMsgPro",   		/* ÈÎÎñÃû    */
                 512,             		/* ÈÎÎñÕ»´óÐ¡£¬µ¥Î»word£¬Ò²¾ÍÊÇ4×Ö½Ú */
                 NULL,           		/* ÈÎÎñ²ÎÊý  */
                 3,               		/* ÈÎÎñÓÅÏÈ¼¶*/
                 &xHandleTaskMsgPro );  /* ÈÎÎñ¾ä±ú  */
	
	
	xTaskCreate( vTaskStart,     		/* ÈÎÎñº¯Êý  */
                 "vTaskStart",   		/* ÈÎÎñÃû    */
                 512,            		/* ÈÎÎñÕ»´óÐ¡£¬µ¥Î»word£¬Ò²¾ÍÊÇ4×Ö½Ú */
                 NULL,           		/* ÈÎÎñ²ÎÊý  */
                 4,              		/* ÈÎÎñÓÅÏÈ¼¶*/
                 &xHandleTaskStart );   /* ÈÎÎñ¾ä±ú  */
}
=======
#include "includes.h"
/*****************å‡½æ•°å£°æ˜Ž*************/
static void vTaskFLASH(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void vTaskMsgPro(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void AppTaskCreate (void);
/*****************å˜é‡å£°æ˜Ž**************/
static TaskHandle_t xHandleTaskFLASH = NULL;
static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskMsgPro = NULL;
static TaskHandle_t xHandleTaskStart = NULL;
/**
  * @brief  ä¸»å¾ªçŽ¯
  * @param  None
  * @retval None
  */
int main(void)
{         
          LCD_Init();
          KEY_Init();
          LED_Init();
        //__set_PRIMASK(1); 
        //åˆå§‹åŒ– RTUæ¨¡å¼ ä»Žæœºåœ°å€ä¸º1 USART1 9600 æ— æ ¡éªŒ
          eMBInit(MB_RTU, 0x01, 0x01, 9600, MB_PAR_NONE);
        //å¯åŠ¨FreeModbus 
          eMBEnable();
        // åˆ›å»ºä»»åŠ¡
        AppTaskCreate();
                
        /* å¯åŠ¨è°ƒåº¦ï¼Œå¼€å§‹æ‰§è¡Œä»»åŠ¡ */
        vTaskStartScheduler();
        /* 
        å¦‚æžœç³»ç»Ÿæ­£å¸¸å¯åŠ¨æ˜¯ä¸ä¼šè¿è¡Œåˆ°è¿™é‡Œçš„ï¼Œè¿è¡Œåˆ°è¿™é‡Œæžæœ‰å¯èƒ½æ˜¯ç”¨äºŽå®šæ—¶å™¨ä»»åŠ¡æˆ–è€…ç©ºé—²ä»»åŠ¡çš„
        heapç©ºé—´ä¸è¶³é€ æˆåˆ›å»ºå¤±è´¥ï¼Œæ­¤è¦åŠ å¤§FreeRTOSConfig.hæ–‡ä»¶ä¸­å®šä¹‰çš„heapå¤§å°ï¼š
        #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 17 * 1024 ) )
        */
                while(1);
}
/*
*********************************************************************************************************
*	å‡½ æ•° å: vTaskFLASH
*	åŠŸèƒ½è¯´æ˜Ž: æŽ¥å£æ¶ˆæ¯å¤„ç†ï¼Œè¿™é‡Œç”¨ä½œFLASH
*	å½¢    å‚: pvParameters æ˜¯åœ¨åˆ›å»ºè¯¥ä»»åŠ¡æ—¶ä¼ é€’çš„å½¢å‚
*	è¿” å›ž å€¼: æ— 
*   ä¼˜ å…ˆ çº§: 1  (æ•°å€¼è¶Šå°ä¼˜å…ˆçº§è¶Šä½Žï¼Œè¿™ä¸ªè·ŸuCOSç›¸å)
*********************************************************************************************************
*/
//è¦å†™å…¥åˆ°STM32 FLASHçš„å­—ç¬¦ä¸²æ•°ç»„
#define FLASH_SAVE_ADDR  0X08020000   
#define SIZE sizeof(FreeSize)	 	//æ•°ç»„é•¿åº¦
u8 FreeSize[]={"STM32 ModbusTEST"};  
u8 datatemp[SIZE];   	
//è®¾ç½®FLASH ä¿å­˜åœ°å€(å¿…é¡»ä¸ºå¶æ•°ï¼Œä¸”å…¶å€¼è¦å¤§äºŽæœ¬ä»£ç æ‰€å ç”¨FLASHçš„å¤§å°+0X08000000)
static void vTaskFLASH(void *pvParameters)
{
   
    while(1)
    {
       //STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
      //STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)FreeSize,SIZE);
      vTaskDelay(100);
    }
}

/*
*********************************************************************************************************
*	å‡½ æ•° å: vTaskLED
*	åŠŸèƒ½è¯´æ˜Ž: LEDé—ªçƒ	
*	å½¢    å‚: pvParameters æ˜¯åœ¨åˆ›å»ºè¯¥ä»»åŠ¡æ—¶ä¼ é€’çš„å½¢å‚
*	è¿” å›ž å€¼: æ— 
*   ä¼˜ å…ˆ çº§: 2  
*********************************************************************************************************
*/
static void vTaskLED(void *pvParameters)
{
    /* LEDé—ªçƒ */
    while(1)
    {
         LED0_ON();
         vTaskDelay(100);
         LED0_OFF();
    }
}

/*
*********************************************************************************************************
*	å‡½ æ•° å: vTaskMsgPro
*	åŠŸèƒ½è¯´æ˜Ž: ä¿¡æ¯å¤„ç†ï¼Œè¿™é‡Œæ˜¯ç”¨ä½œLEDé—ªçƒ	
*	å½¢    å‚: pvParameters æ˜¯åœ¨åˆ›å»ºè¯¥ä»»åŠ¡æ—¶ä¼ é€’çš„å½¢å‚
*	è¿” å›ž å€¼: æ— 
*   ä¼˜ å…ˆ çº§: 3  
*********************************************************************************************************
*/
static void vTaskMsgPro(void *pvParameters)
{
    while(1)
    {
        
        eMBPoll(); 
        vTaskDelay(300);
    }
}

/*
*********************************************************************************************************
*	å‡½ æ•° å: vTaskStart
*	åŠŸèƒ½è¯´æ˜Ž: å¯åŠ¨ä»»åŠ¡ï¼Œä¹Ÿå°±æ˜¯æœ€é«˜ä¼˜å…ˆçº§ä»»åŠ¡ï¼Œè¿™é‡Œç”¨ä½œLEDé—ªçƒ
*	å½¢    å‚: pvParameters æ˜¯åœ¨åˆ›å»ºè¯¥ä»»åŠ¡æ—¶ä¼ é€’çš„å½¢å‚
*	è¿” å›ž å€¼: æ— 
*   ä¼˜ å…ˆ çº§: 4  
*********************************************************************************************************
*/
static void vTaskStart(void *pvParameters)
{
    while(1)
    {
        KEY_red();
        LED_Poll();
        vTaskDelay(400);
    }
}

/*
*********************************************************************************************************
*	å‡½ æ•° å: AppTaskCreate
*	åŠŸèƒ½è¯´æ˜Ž: åˆ›å»ºåº”ç”¨ä»»åŠ¡
*	å½¢    å‚ï¼šæ— 
*	è¿” å›ž å€¼: æ— 
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
    xTaskCreate( vTaskFLASH,   	/* ä»»åŠ¡å‡½æ•°  */
                 "vTaskFLASH",     	/* ä»»åŠ¡å    */
                 512,               	/* ä»»åŠ¡æ ˆå¤§å°ï¼Œå•ä½wordï¼Œä¹Ÿå°±æ˜¯4å­—èŠ‚ */
                 NULL,              	/* ä»»åŠ¡å‚æ•°  */
                 1,                 	/* ä»»åŠ¡ä¼˜å…ˆçº§*/
                 &xHandleTaskFLASH );  /* ä»»åŠ¡å¥æŸ„  */
	
	
	xTaskCreate( vTaskLED,    		/* ä»»åŠ¡å‡½æ•°  */
                 "vTaskLED",  		/* ä»»åŠ¡å    */
                 512,         		/* ä»»åŠ¡æ ˆå¤§å°ï¼Œå•ä½wordï¼Œä¹Ÿå°±æ˜¯4å­—èŠ‚ */
                 NULL,        		/* ä»»åŠ¡å‚æ•°  */
                 2,           		/* ä»»åŠ¡ä¼˜å…ˆçº§*/
                 &xHandleTaskLED ); /* ä»»åŠ¡å¥æŸ„  */
	
	xTaskCreate( vTaskMsgPro,     		/* ä»»åŠ¡å‡½æ•°  */
                 "vTaskMsgPro",   		/* ä»»åŠ¡å    */
                 512,             		/* ä»»åŠ¡æ ˆå¤§å°ï¼Œå•ä½wordï¼Œä¹Ÿå°±æ˜¯4å­—èŠ‚ */
                 NULL,           		/* ä»»åŠ¡å‚æ•°  */
                 3,               		/* ä»»åŠ¡ä¼˜å…ˆçº§*/
                 &xHandleTaskMsgPro );  /* ä»»åŠ¡å¥æŸ„  */
	
	
	xTaskCreate( vTaskStart,     		/* ä»»åŠ¡å‡½æ•°  */
                 "vTaskStart",   		/* ä»»åŠ¡å    */
                 512,            		/* ä»»åŠ¡æ ˆå¤§å°ï¼Œå•ä½wordï¼Œä¹Ÿå°±æ˜¯4å­—èŠ‚ */
                 NULL,           		/* ä»»åŠ¡å‚æ•°  */
                 4,              		/* ä»»åŠ¡ä¼˜å…ˆçº§*/
                 &xHandleTaskStart );   /* ä»»åŠ¡å¥æŸ„  */
}
>>>>>>> 9fd0c1753aa48fb6da98c1c2c579a419d710233d:FreeModbus+FreeRTOS-8.0/User/main.c
