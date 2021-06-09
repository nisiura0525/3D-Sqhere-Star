#include"libOne.h"
//頂点位置の構造体
struct POS {  //頂点の構造体
    float x, y, z;
};
//ゲームメイン
void gmain() {
    window(1000, 1000);
    //頂点の数
    int numCorners = 10; //前から見て八角形
    int numRings = 4;//10角形を複数用意するためのリングス
    int numVertices = numCorners * numRings;
    //ナムコーナーズとナムリングスを掛けた頂点をナムヴァーティシーズ頂点数
    int Co = numCorners;
    float deg = 360.0f / numCorners;//x,y用の角度
    float deg2 = 360.0f / 6;//x,z用の角度
    angleMode(DEGREES);

    struct POS* op = new POS[numVertices]; //動的確保
    //opをナムヴァーティシーズ分だけ用意した　op（ヴァーティシーズ
    //八角形の頂点をsin、cosを使って表示してい
    for (int j = 0;j <numRings;j++) {
        float r = sin(deg2 * j);
        float z = cos(deg2 * j)*0.3;
        for (int i = 0;i < numCorners;i++){
            float radius = 0.5f + 0.5f * (i % 2); 
            //iは０から７までしか変化しなくｊの分まで変化させる
            //１元配列を２次元的使用する方法
            int k = j * numCorners + i;        
            op[k].x = sin(deg * i)*radius *r;
            op[k].y = -cos(deg * i)*radius *r;
            op[k].z = z;//1.0f - 2.0f / (numRings - 1) * j;
            //奥行のｚの値、左から計算して行くと0.5,1,0,-0.5,-1
        }
    }
    struct POS* p = new POS[numVertices]; //pをナムヴァーティシーズ分だけ用意した


    int state = 0;
    int flug = 0;
    while (notQuit) {
        clear(0);
        if (flug == 0) {
            deg += 1;
        }
        float s = sin(deg);
        float c = cos(deg);
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        if (isTrigger(KEY_SPACE)) {
            ++flug;
            flug %= 2;
        }
        for (int i = 0;i < numVertices;i++) {
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            //最初から座標が1個指定してあって
            //その座標をsin・cosを使って回転させていく
            //適当に打った座標を回転させることができる
            //p[i].x = op[i].x;
            else if (state == 1) {
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].x = op[i].x;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            //p[i].z = op[i].z + s; //Ｚ（奥行）の運動が大きいほどX,Yの座標が小さくなる
            p[i].z += 5;

            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
        }
        mathAxis(0.5);
        stroke(255, 255, 0);
        for (int i = 0;i < numVertices;i++) {
            int j = i + 1;
            if (j % numCorners == 0) { j -= numCorners; }
            strokeWeight(6);
            mathPoint(p[i].x, p[i].y);
            strokeWeight(2);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);

            if (j < numVertices - numCorners) {
                j = i + numCorners;
                mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }
        }
    }
    delete[]p;
    delete[]op;
}

/*
#include"libOne.h"
//頂点位置の構造体
struct POS {  //頂点の構造体
    float x, y, z;
};
//ゲームメイン
void gmain() {
    window(1000, 1000);
    //頂点の数
    int numCorners = 8; //前から見て八角形
    int numRings = numCorners / 2 + 1;//先々八角形を複数用意するためのリングス
    int numVertices = numCorners * numRings;
    //ナムコーナーズとナムリングスを掛けた頂点をナムヴァーティシーズ頂点数    

    float deg = 360.0f / numCorners;
    angleMode(DEGREES);

    struct POS* op = new POS[numVertices]; //動的確保
    //opをナムヴァーティシーズ分だけ用意した　op（ヴァーティシーズ
    //八角形の頂点をsin、cosを使って表示してい
    for (int j = 0;j < numRings;j++) {
        float r = sin(deg * j);
        float z = cos(deg * j);
        for (int i = 0;i < numCorners;i++) {
            //iは０から７までしか変化しなくｊの分まで変化させる
            //１元配列を２次元的使用する方法
            int k = j * numCorners + i;
            op[k].x = sin(deg * i) * r;
            op[k].y = cos(deg * i) * r;
            op[k].z = z;//1.0f - 2.0f / (numRings-1) * j;
            //奥行のｚの値、左から計算して行くと0.5,1,0,-0.5,-1
        }
    }
    struct POS* p = new POS[numVertices]; //pをナムヴァーティシーズ分だけ用意した


    int state = 0;
    int flug = 0;
    while (notQuit) {
        clear(0);
        if (flug == 0) {
            deg += 1;
        }
        float s = sin(deg);
        float c = cos(deg);
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        if (isTrigger(KEY_SPACE)) {
            ++flug;
            flug %= 2;
        }
        for (int i = 0;i < numVertices;i++) {
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            //最初から座標が1個指定してあって
            //その座標をsin・cosを使って回転させていく
            //適当に打った座標を回転させることができる
            //p[i].x = op[i].x;
            else if (state == 1) {
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].x = op[i].x;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            //p[i].z = op[i].z + s; //Ｚ（奥行）の運動が大きいほどX,Yの座標が小さくなる
            p[i].z += 5;

            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
        }
        mathAxis(0.5);
        stroke(200, 255, 255);
        for (int i = 0;i < numVertices;i++) {
            int j = i + 1;
            if (j % numCorners == 0) { j -= numCorners; }
            strokeWeight(6);
            mathPoint(p[i].x, p[i].y);
            strokeWeight(2);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);

            if (j < numVertices - numCorners) {
                j = i + numCorners;
                mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }
        }
    }
    delete[]p;
    delete[]op;
}
*/
/*
#include"libOne.h"
//頂点位置の構造体
struct POS {
    float x, y, z;
};
void setSphere(struct POS* op, int numCorners, int numRings) {
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    for (int j = 0; j < numRings; j++) {
        float r = sin(deg * j);
        float z = cos(deg * j);
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(deg * i) * r;
            op[k].y = cos(deg * i) * r;
            op[k].z = z;
        }
    }
}
void setCylinder(struct POS* op, int numCorners, int numRings) {
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    for (int j = 0; j < numRings; j++) {
        for (int i = 0; i < numCorners; i++) {
            int k = j * numCorners + i;
            op[k].x = sin(deg * i);
            op[k].y = cos(deg * i);
            op[k].z = 1.0f - 2.0f / (numRings - 1) * j;
        }
    }
}
//ゲームメイン
void gmain() {
    window(1000, 1000, full);
    //頂点の数
    int numCorners = 32;
    int numRings = numCorners / 2 + 1;
    int numVertices = numCorners * numRings;
    //元の頂点位置（ループ中も保持されている。変化しない）
    struct POS* op = new POS[numVertices];
    float deg = 360.0f / numCorners;
    angleMode(DEGREES);
    setSphere(op, numCorners, numRings);
    //変更後の頂点位置の入れ物（ループするたびに変化する）
    struct POS* p = new POS[numVertices];
    //元の頂点位置を回転させる角度
    deg = 0;
    //このstateが0の時Y軸、1の時X軸回転する
    int state = 0;
    int sw = 1;
    //メインループ
    while (notQuit) {
        //頂点位置変更
        if (isTrigger(KEY_SPACE)) {
            sw = 1 - sw;
            if (sw == 0)setCylinder(op, numCorners, numRings);
            else setSphere(op, numCorners, numRings);
        }
        //あらかじめsin,cosを計算しておく
        float s = sin(deg);
        float c = cos(deg);
        deg++;
        //stateの変更
        if (deg > 360) {
            deg = 0;
            ++state %= 2;
        }
        //配列opの座標を変換して配列pに書き込む
        // ( 配列opの位置は変わらない )
        for (int i = 0; i < numVertices; i++) {
            //回転
            if (state == 0) {
                p[i].x = op[i].x * c + op[i].z * -s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * s + op[i].z * c;
            }
            else {
                p[i].x = op[i].x;
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            //奥に移動
            p[i].z += 5;
            //遠くの座標を小さくする
            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
        }
        //頂点位置を線で結び球体にする
        clear(0);
        mathAxis(0.5);//クリア色と同じで軸は見えないが必要な命令
        stroke(160, 200, 255);
        for (int i = 0; i < numVertices; i++) {
            //頂点
            //strokeWeight(6);
            //mathPoint(p[i].x, p[i].y);
            //リングの頂点を線で結ぶ
            int j = i + 1;
            if (j % numCorners == 0)j -= numCorners;
            strokeWeight(2);
            mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            //前後の頂点を線で結ぶ
            if (i < numVertices - numCorners) {
                j = i + numCorners;
                mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
            }
        }
    }
    delete[]op;
    delete[]p;
}
*/