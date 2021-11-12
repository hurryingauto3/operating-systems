#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

struct msgbuf {
   long mtype;
   char msgtxt[200];
};

int main()
{
   struct msgbuf msg;
   int msgid;
   key_t key;

   if((key==ftok("msg_snd.c", 'b')) == -1)
   {
      perror("key");
      exit(1);
   }

   if((msgid=msgget(key, 0644|IPC_CREAT)) == -1)
   {
      perror("key");
      exit(1);
   }

   printf("msgsend [INFO] The message id is: %d\n", msgid);
   printf("msgsend [PROMPT] Enter a text: ");
   msg.mtype = 1; 

   while(1)
   {
      if(msgrcv(msgid, &msg, sizeof(msg),1,0) == -1)
      {
         perror("msgrcv");
         exit(1);
      }
      printf("message received [INFO] Message: %s\n", msg.msgtxt);
   }

   if(msgctl(msgid, IPC_RMID, NULL) == -1)
   {
      perror("msgctl");
      exit(1);
   }
   return 0;
}
 
