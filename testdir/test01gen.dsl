-- Load+create Data and shut down of tbl1 which has 1 attribute only
create(db,"db1")
create(tbl,"tbl1",db1,2)
create(col,"col1",db1.tbl1)
create(col,"col2",db1.tbl1)
load("/cs165/staff_test/data1_generated.csv")
shutdown
