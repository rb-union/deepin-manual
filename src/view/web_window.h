/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEEPIN_MANUAL_VIEW_WEB_WINDOW_H
#define DEEPIN_MANUAL_VIEW_WEB_WINDOW_H

#include <DMainWindow>

#include "controller/search_result.h"

class QWebEngineView;

namespace dman {

class ImageViewer;
class ImageViewerProxy;
class SearchCompletionWindow;
class SearchManager;
class SearchProxy;
class TitleBar;
class TitleBarProxy;

class WebWindow : public Dtk::Widget::DMainWindow {
  Q_OBJECT
  Q_PROPERTY(QString appName READ appName WRITE setAppName)

 public:
  explicit WebWindow(SearchManager* search_manager, QWidget* parent = nullptr);
  ~WebWindow() override;

  // Get app name of manual currently presented.
  const QString& appName() const {
    return app_name_;
  }

 public slots:
  void setAppName(const QString& app_name);

 protected:
  // Update width of title bar when main window is resized.
  void resizeEvent(QResizeEvent* event) override;

 private:
  void initConnections();
  void initUI();

  QString app_name_;
  SearchManager* search_manager_ = nullptr;
  SearchProxy* search_proxy_ = nullptr;
  SearchCompletionWindow* completion_window_ = nullptr;
  ImageViewer* image_viewer_ = nullptr;
  ImageViewerProxy* image_viewer_proxy_ = nullptr;
  TitleBar* title_bar_ = nullptr;
  TitleBarProxy* title_bar_proxy_ = nullptr;
  QWebEngineView* web_view_ = nullptr;

 private slots:
  void onSearchEditFocusOut();
  void onSearchResult(const QString& app_name,
                      const QString& keyword,
                      const SearchResultList& result);
  void onSearchTextChanged(const QString& text);
  void onWebPageLoadFinished(bool ok);
};

}  // namespace dman

#endif  // DEEPIN_MANUAL_VIEW_WEB_WINDOW_H
