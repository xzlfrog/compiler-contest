# Compiler2025-BBBian

# 编译器项目架构说明

## 项目架构概述

```
测试源码 ——> AST格式 ——> SSA内存格式 ——> ARM码
                                ↓
                        (同时生成LLVM的文字格式)
```

## 阶段说明

### 1. 前端 - Flex+Yacc生成AST

**作用**：将源代码转换为抽象语法树(AST)格式

**理由**：
- 树结构可以方便地递归生成中间码
- 代码分离有显著的好处
- 使用Lex+Yacc工具生成

**待解决问题**：
- AST的结构设计（节点类型、子节点等）

### 2. 中端 - LLVM

**内存格式**：类比三地址码格式，优先采用SSA形式

**LLVM文字格式的作用**：
1. 方便检查生成是否正确
2. 方便后续性能优化（如果有）
3. 从学习角度，LLVM是非常重要的工具

**待解决问题**：
- LLVM IR的语法与常用指令（如 alloca, load, store, add, br, phi）
- 如何从SSA结构映射生成LLVM IR/ARM码？
  - 课程中SSA是链式结构体，通过遍历生成
  - 学长代码中使用C++类实现（待研究具体实现方式）

### 3. 后端 - ARM

**待解决问题**：
- ARM汇编语言基本格式

## 实现要点

1. **AST生成**：使用Lex+Yacc工具组合
2. **中间表示**：采用SSA形式的三地址码
3. **双输出**：
   - 内存中的SSA格式（用于生成ARM码）
   - LLVM文字格式（用于验证和优化）

## 入门指南

为了让您轻松开始使用GitLab，以下是推荐的后续步骤列表。

已经是专家了？只需编辑此README.md并使其成为您自己的。想要更简单？[使用底部的模板](#editing-this-readme)！

## 添加您的文件

- [ ] [创建](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file)或[上传](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file)文件
- [ ] [使用命令行添加文件](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line)或通过以下命令推送现有的Git仓库：

```
cd existing_repo
git remote add origin https://gitlab.eduxiji.net/T202510614206372/compiler2025-bbbian.git
git branch -M main
git push -uf origin main
```

## 与您的工具集成

- [ ] [设置项目集成](https://gitlab.eduxiji.net/T202510614206372/compiler2025-bbbian/-/settings/integrations)

## 与团队协作

- [ ] [邀请团队成员和协作者](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [创建新的合并请求](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [自动从合并请求关闭问题](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [启用合并请求批准](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [在流水线成功时自动合并](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## 测试与部署

使用GitLab内置的持续集成功能。

- [ ] [开始使用GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [使用静态应用程序安全测试(SAST)分析代码中的已知漏洞](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [使用自动部署功能部署到Kubernetes、Amazon EC2或Amazon ECS](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [使用基于拉取的部署改进Kubernetes管理](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [设置受保护的环境](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# 编辑此README

当您准备好将此README变为自己的版本时，只需编辑此文件并使用以下方便的模板（或随意按您想要的结构组织——这只是一个起点！）。感谢[makeareadme.com](https://www.makeareadme.com/)提供此模板。

## 优秀README的建议

每个项目都不同，因此请考虑哪些部分适用于您的项目。模板中使用的部分是对大多数开源项目的建议。同时请记住，虽然README可能过长且过于详细，但过长总比过短好。如果您认为README太长，可以考虑使用另一种形式的文档，而不是删除信息。

## 名称

为您的项目选择一个自解释的名称。

## 描述

让人们具体了解您的项目能做什么。提供背景信息，并添加指向访问者可能不熟悉的任何参考资料的链接。还可以在此处添加“功能”列表或“背景”子部分。如果您的项目有替代方案，这是列出差异化因素的好地方。

## 徽章

在某些README上，您可能会看到传达元数据的小图像，例如项目的所有测试是否通过。您可以使用Shields添加一些徽章到您的README中。许多服务还提供了添加徽章的说明。

## 视觉效果

根据您制作的内容，包含截图甚至视频可能是个好主意（您会经常看到GIF而不是实际视频）。像ttygif这样的工具可以提供帮助，但也可以查看Asciinema以获取更复杂的方法。

## 安装

在特定的生态系统中，可能有常见的安装方式，例如使用Yarn、NuGet或Homebrew。但请考虑到阅读您README的可能是一个新手，需要更多指导。列出具体步骤有助于消除歧义，并让人们尽快使用您的项目。如果它仅在特定上下文中运行，例如特定的编程语言版本或操作系统，或者有需要手动安装的依赖项，还需添加“要求”子部分。

## 使用

大量使用示例，并尽可能展示预期输出。在README中内联展示您可以演示的最小使用示例非常有帮助，同时如果更复杂的示例太长而无法合理地包含在README中，可以提供其链接。

## 支持

告诉人们可以去哪里寻求帮助。可以是问题跟踪器、聊天室、电子邮件地址等的任意组合。

## 路线图

如果您对未来的版本有想法，最好在README中列出它们。

## 贡献

说明您是否接受贡献以及接受贡献的要求是什么。

对于想要更改您的项目的人，提供一些关于如何开始的文档会很有帮助。也许有一个他们应该运行的脚本或一些需要设置的环境变量。明确这些步骤。这些说明也可能对未来的您有用。

您还可以记录用于检查代码或运行测试的命令。这些步骤有助于确保代码质量，并减少更改无意中破坏某些内容的可能性。如果运行测试需要外部设置（例如启动Selenium服务器以在浏览器中进行测试），则提供运行测试的说明尤其有用。

## 作者与致谢

向为项目做出贡献的人表示感谢。

## 许可证

对于开源项目，说明其许可证。

## 项目状态

如果您对项目的精力或时间已经耗尽，请在README顶部添加说明，表示开发已放缓或完全停止。有人可能会选择分叉您的项目或自愿作为维护者或所有者介入，从而使您的项目得以继续。您还可以明确请求维护者。
