// ----------------------------------------------------------------
//  Name:           BaseMethod.hpp
//  Description:    提供了一般的多叉树，层次树的基本接口申明
//					也就是要求节点内部必须提供的接口
//					返回引用可以作为左值，修改内部数据
//					返回const不可以修改
// ----------------------------------------------------------------
//					不管HNode内部定义如何，有这些接口就可以作为
//					HTree的参数使用
// ----------------------------------------------------------------
//					</所有的Node类都继承于BaseMethod类/>
//					</HTree中只是调用这些基本接口/>
//					</保证了结构和算法的相对独立性/>
// ----------------------------------------------------------------
//  Create Time:	4/9/2009 
//	Author:			RenYaFei
// ----------------------------------------------------------------