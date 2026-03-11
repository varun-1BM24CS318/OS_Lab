#include<stdio.h>

struct process{
    int pid,at,bt,rt,pr,ct,tat,wt;
};

void priority_preemptive(struct process p[],int n){
    int time=0,completed=0,i,index;
    int min;

    while(completed<n){
        min=9999;
        index=-1;

        for(i=0;i<n;i++){
            if(p[i].at<=time && p[i].rt>0){
                if(p[i].pr < min){
                    min=p[i].pr;
                    index=i;
                }
                else if(p[i].pr==min){
                    if(p[i].at < p[index].at)
                        index=i;
                }
            }
        }

        if(index!=-1){
            p[index].rt--;
            time++;

            if(p[index].rt==0){
                p[index].ct=time;
                completed++;
            }
        }
        else{
            time++;
        }
    }

    float avg_tat=0,avg_wt=0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;

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
        p[i].rt=p[i].bt;
    }

    priority_preemptive(p,n);

    return 0;
}
