#include<stdio.h>

struct process{
    int pid,at,bt,pr,ct,tat,wt,done;
};
void priority_nonPreemptive(struct process p[],int n){
int i,time=0,completed=0,min,index;
 while(completed<n){
        min=9999;
        index=-1;

        for(i=0;i<n;i++){
            if(p[i].at<=time && p[i].done==0){
                if(p[i].pr<min){
                    min=p[i].pr;
                    index=i;
                }
            }
        }

        if(index!=-1){
            time+=p[index].bt;
            p[index].ct=time;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;
            p[index].done=1;
            completed++;
        }
        else
            time++;
    }

    float avg_tat=0,avg_wt=0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++){
        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,p[i].at,p[i].bt,p[i].pr,
        p[i].ct,p[i].tat,p[i].wt);
    }

    printf("\nAverage TAT = %.2f",avg_tat/n);
    printf("\nAverage WT = %.2f",avg_wt/n);
}
int main(){
    int n,i;
    struct process p[20];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter AT BT Priority for P%d: ",i+1);
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pr);
        p[i].pid=i+1;
        p[i].done=0;
    }

    priority_nonPreemptive(p,n);
    return 0;
}
