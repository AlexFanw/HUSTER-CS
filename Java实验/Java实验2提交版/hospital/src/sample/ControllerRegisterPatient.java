package sample;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import org.controlsfx.control.textfield.AutoCompletionBinding;
import org.controlsfx.control.textfield.TextFields;

import javax.swing.*;
import java.io.IOException;
import java.math.BigDecimal;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.Date;

public class ControllerRegisterPatient {
    @FXML
    private TextField field_depname;
    @FXML
    private TextField field_docname;
    @FXML
    private TextField field_regcat;
    @FXML
    private TextField field_regname;
    @FXML
    private TextField field_payment;
    @FXML
    private TextField field_bill;
    @FXML
    private TextField field_change;
    @FXML
    private TextField field_regnum;
    @FXML
    private Button btn_confirm;
    @FXML
    private Button btn_clear;
    @FXML
    private Button btn_quit;
    private ArrayList<String> depnameList; //存放科室名称信息
    private ArrayList<String> docnameList; //存放医生名称信息
    private ArrayList<String> regcatList; //存放号种类别
    private ArrayList<String> regnameList; //存放号种名称
    private boolean isMoneyEnough; //余额是否充足

    public void initialize() throws SQLException { //初始化
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            
            return;
        }
        isMoneyEnough=false;
        depnameList=new ArrayList<>();
        docnameList=new ArrayList<>();
        regcatList=new ArrayList<>();
        regnameList=new ArrayList<>();
        field_bill.setEditable(false);
        field_change.setEditable(false);
        field_regnum.setEditable(false);
        String sql="select * from department";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        ResultSet rs=preparedStatement.executeQuery(); //取出表department中的信息
        while(rs.next()){
            String depname=rs.getString("depid")+" "+rs.getString("name")+" "+rs.getString("py");
            depnameList.add(depname);
        }
        AutoCompletionBinding binding=TextFields.bindAutoCompletion(field_depname,depnameList); //绑定，用于科室名称信息的自动补全
        binding.setVisibleRowCount(3);
        binding.setPrefWidth(150);
        preparedStatement.close();
        connection.close();
    }
    public void on_field_docname_clicked() throws SQLException { //点击时更新医生姓名下拉补全列表
        docnameList.clear();
        if(field_depname.getText().length()==12||field_depname.getText().length()==14){
            Connection connection=new MySQLConnector().connection();
            if(connection==null){
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText("连接数据库失败!");
                alert.showAndWait();
                return;
            }
            String[] triple=field_depname.getText().split("\\s+");
            String sql="select * from department where depid=? and name=? and py=?";
            PreparedStatement preparedStatement=connection.prepareStatement(sql);
            preparedStatement.setString(1,triple[0]);
            preparedStatement.setString(2,triple[1]);
            preparedStatement.setString(3,triple[2]);
            ResultSet rs=preparedStatement.executeQuery();
            if(!(rs.next())){ //找不到该科室
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText("科室信息错误");
                alert.showAndWait();
                preparedStatement.close();
                connection.close();
                return;
            }
            String rsDepid=triple[0];
            String sql2="select * from doctor where depid=?";
            preparedStatement=connection.prepareStatement(sql2);
            preparedStatement.setString(1,rsDepid);
            rs=preparedStatement.executeQuery();
            while(rs.next()){ //将对应科室的医生加入下拉补全列表
                String docname=rs.getString("docid")+" "+rs.getString("name")+" "+rs.getString("py");
                docnameList.add(docname);
            }
            AutoCompletionBinding binding=TextFields.bindAutoCompletion(field_docname,docnameList); //绑定，用于医生姓名信息的自动补全
            binding.setVisibleRowCount(3);
            binding.setPrefWidth(150);
            preparedStatement.close();
            connection.close();
        }
        else{
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("科室信息有误");
            alert.showAndWait();
        }

    }
    public void on_field_regcat_clicked() throws SQLException { //点击时更新号种类别下拉补全列表
        regcatList.clear();
        if(field_docname.getText().length()==12||field_docname.getText().length()==14){
            Connection connection=new MySQLConnector().connection();
            if(connection==null){
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
                return;
            }
            String[] triple=field_docname.getText().split("\\s+");
            String sql="select * from doctor where docid=? and name=? and py=?";
            PreparedStatement preparedStatement=connection.prepareStatement(sql);
            preparedStatement.setString(1,triple[0]);
            preparedStatement.setString(2,triple[1]);
            preparedStatement.setString(3,triple[2]);
            ResultSet rs=preparedStatement.executeQuery();
            if(!(rs.next())){ //找不到该医生
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText("医生不存在");
                alert.showAndWait();
                preparedStatement.close();
                connection.close();
                return;
            }
            regcatList.add("普通号");
            boolean isSp=rs.getBoolean("speciallist");
            if(isSp)
                regcatList.add("专家号");
            AutoCompletionBinding binding=TextFields.bindAutoCompletion(field_regcat,regcatList); //绑定，用于号种类别信息的自动补全
            binding.setPrefWidth(150);
            if((!isSp)&&field_regcat.getText().equals("专家号")){
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText("无该医生的专家号");
                alert.showAndWait();
                field_regcat.clear();
            }
            preparedStatement.close();
            connection.close();
        }
        else{
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("医生信息有误");
            alert.showAndWait();
        }
    }
    public void on_field_regname_clicked() throws SQLException { //生成号种信息
        regnameList.clear();
        if(field_regcat.getText().equals("普通号")||field_regcat.getText().equals("专家号")){
            Connection connection=new MySQLConnector().connection();
            if(connection==null){
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
                return;
            }
            boolean isSp;
            String depid;
            isSp=!field_regcat.getText().equals("普通号");
            String[] triple=field_depname.getText().split("\\s+");
            depid=triple[0];
            String sql="select * from register_category where depid=? and speciallist=?";
            PreparedStatement preparedStatement=connection.prepareStatement(sql);
            preparedStatement.setString(1,depid);
            preparedStatement.setBoolean(2,isSp);
            ResultSet rs=preparedStatement.executeQuery();
            while(rs.next()){ //将号种名称信息加入到下拉补全列表
                String regname=rs.getString("catid")+" "+rs.getString("name")+" "+rs.getString("py");
                regnameList.add(regname);
            }
            AutoCompletionBinding binding=TextFields.bindAutoCompletion(field_regname,regnameList);
            binding.setVisibleRowCount(3);
            binding.setPrefWidth(150);
            //接下来判断病人余额是否充足
            if(field_regname.getText().length()>=16){
                String pid=new ControllerLoginPatient().getLoginedPid();
                String sql2="select * from patient where pid=?";
                preparedStatement=connection.prepareStatement(sql2);
                preparedStatement.setString(1,pid);
                rs=preparedStatement.executeQuery();
                if(!(rs.next())){
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setHeaderText("未查询到此病人");
                    alert.showAndWait();
                    preparedStatement.close();
                    connection.close();
                    return;
                }
                String balance=rs.getString("balance"); //得到病人余额
                triple=field_regname.getText().split("\\s+");
                String catid=triple[0];
                String sql3="select * from register_category where catid=?";
                preparedStatement=connection.prepareStatement(sql3);
                preparedStatement.setString(1,catid);
                rs=preparedStatement.executeQuery();
                if(!(rs.next())){
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setHeaderText("无此号种");
                    alert.showAndWait();
                    preparedStatement.close();
                    connection.close();
                    return;
                }
                String bill=rs.getString("reg_fee");
                field_bill.setText(bill);
                field_bill.setDisable(true);
                float balanceNum=Float.parseFloat(balance);
                float billNum=Float.parseFloat(bill);
                if(balanceNum>billNum){ //病人预存金额充足
                    isMoneyEnough=true;
                    float changeNum=balanceNum-billNum;
                    field_payment.setText("余额充足:"+balance);
                    field_payment.setDisable(true);
                    field_change.setText("付后余额:"+changeNum);
                    field_change.setDisable(true);
                }
                else //预存金额不足
                    isMoneyEnough=false;
            }
            preparedStatement.close();
            connection.close();
        }
        else{Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("信息有误");
            alert.showAndWait();}
    }
    public void on_field_change_clicked(){ //预存金额不足时，根据输入来计算找零
        if(!isMoneyEnough){
            if(!field_payment.getText().isEmpty()){
                float paymentNum=Float.parseFloat(field_payment.getText());
                float billNum=Float.parseFloat(field_bill.getText());
                if(paymentNum<billNum){
                    Alert alert = new Alert(Alert.AlertType.INFORMATION);
                    alert.setHeaderText("金额不足");
                    alert.showAndWait();
                    return;
                }
                float changeNum=paymentNum-billNum;
                field_change.setText(String.valueOf(changeNum));
            }
        }
    }
    public void on_field_regnum_clicked() throws SQLException { //点击获取挂号号码
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        String sql="select count(*) from register";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        ResultSet rs=preparedStatement.executeQuery();
        rs.next();
        int regnum=rs.getInt(1)+1;
        field_regnum.setText(String.valueOf(regnum));
        preparedStatement.close();
        connection.close();
    }

    //回车键确认
    public void onEnter() throws SQLException {
        on_btn_confirm_clicked();
    }
    public void on_btn_confirm_clicked() throws SQLException { //确认按钮
        Connection connection=new MySQLConnector().connection();
        if(connection==null){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("连接数据库失败!");
            alert.showAndWait();
            return;
        }
        int num=Integer.parseInt(field_regnum.getText());
        String reg_id=String.format("%06d",num);
        String catid=field_regname.getText().substring(0,6);
        String docid=field_docname.getText().substring(0,6);
        String pid=new ControllerLoginPatient().getLoginedPid();
        int current_reg_count;
        boolean unreg=true;
        BigDecimal reg_fee=new BigDecimal(field_bill.getText());
        String reg_datetime=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
        String sql="select max(current_reg_count) from register where catid=? and reg_datetime REGEXP ?";
        PreparedStatement preparedStatement=connection.prepareStatement(sql);
        preparedStatement.setString(1,catid);
        String today="^"+reg_datetime.substring(0,10); //获得当天日期
        preparedStatement.setString(2,today);
        ResultSet rs=preparedStatement.executeQuery();
        if(!rs.next()) //该号种当天还没有人挂过
            current_reg_count=1;
        else{ //检查该号种挂号次数是否已满
            current_reg_count=rs.getInt(1)+1;
            String sql2="select max_reg_number from register_category where catid=?";
            preparedStatement=connection.prepareStatement(sql2);
            preparedStatement.setString(1,catid);
            rs=preparedStatement.executeQuery();
            rs.next();
            int max_reg_num=rs.getInt(1);
            if(current_reg_count>max_reg_num){ //该号种挂号次数已满
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText("挂号失败，人数已满");
                alert.showAndWait();
                preparedStatement.close();
                connection.close();
                return;
            }
        }
        if(!isMoneyEnough){
            if(field_change.getText().isEmpty()||Float.parseFloat(field_payment.getText())<Float.parseFloat(field_bill.getText())){
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText("金额不足");
                alert.showAndWait();
                preparedStatement.close();
                connection.close();
                return;
            }
        }
        String sql3="insert into register values(?,?,?,?,?,?,?,?)";
        preparedStatement=connection.prepareStatement(sql3);
        preparedStatement.setString(1,reg_id);
        preparedStatement.setString(2,catid);
        preparedStatement.setString(3,docid);
        preparedStatement.setString(4,pid);
        preparedStatement.setInt(5,current_reg_count);
        preparedStatement.setBoolean(6,unreg);
        preparedStatement.setBigDecimal(7,reg_fee);
        preparedStatement.setString(8,reg_datetime);
        if(preparedStatement.executeUpdate()>0){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("挂号成功,当前号码:"+reg_id);
            alert.showAndWait();
            if(isMoneyEnough){ //余额更新
                String sql4="update patient set balance=? where pid=?";
                preparedStatement=connection.prepareStatement(sql4);
                float newBalance=Float.parseFloat(field_change.getText().substring(5));
                preparedStatement.setBigDecimal(1,BigDecimal.valueOf(newBalance));
                preparedStatement.setString(2,pid);
                preparedStatement.executeUpdate();
            }
            on_btn_clear_clicked();
        }
        else{
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText("挂号失败");
            alert.showAndWait();
        }
        preparedStatement.close();
        connection.close();
    }
    public void on_btn_clear_clicked() { //清除按钮
        field_bill.setDisable(false);
        field_payment.setDisable(false);
        field_change.setDisable(false);
        field_depname.clear();
        field_docname.clear();
        field_regcat.clear();
        field_regname.clear();
        field_payment.clear();
        field_bill.clear();
        field_change.clear();
        field_regnum.clear();
    }
    public void on_btn_quit_clicked() throws IOException { //退出按钮
        Stage currentStage=(Stage)field_depname.getScene().getWindow();
        currentStage.close(); //关闭当前窗口
        SplitPane root=FXMLLoader.load(getClass().getResource("Login.fxml")); //转到登录界面
        Stage newStage=new Stage();
        newStage.setTitle("登录");
        newStage.setScene(new Scene(root));
        newStage.show();
    }
}
